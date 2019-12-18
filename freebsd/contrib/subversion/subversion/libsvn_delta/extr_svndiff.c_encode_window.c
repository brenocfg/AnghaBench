#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int num_ops; TYPE_4__* new_data; int /*<<< orphan*/  tview_len; int /*<<< orphan*/  sview_len; int /*<<< orphan*/  sview_offset; TYPE_2__ const* ops; } ;
typedef  TYPE_1__ svn_txdelta_window_t ;
struct TYPE_17__ {int action_code; int length; int offset; } ;
typedef  TYPE_2__ const svn_txdelta_op_t ;
struct TYPE_18__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ svn_stringbuf_t ;
struct TYPE_19__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int MAX_INSTRUCTION_LEN ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  append_encoded_int (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn__compress_lz4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  svn__compress_zlib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 unsigned char* svn__encode_uint (unsigned char*,int) ; 
 TYPE_4__* svn_stringbuf__morph_into_string (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (TYPE_3__*,char const*,int) ; 
 TYPE_3__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 
#define  svn_txdelta_new 130 
#define  svn_txdelta_source 129 
#define  svn_txdelta_target 128 

__attribute__((used)) static svn_error_t *
encode_window(svn_stringbuf_t **instructions_p,
              svn_stringbuf_t **header_p,
              const svn_string_t **newdata_p,
              svn_txdelta_window_t *window,
              int version,
              int compression_level,
              apr_pool_t *pool)
{
  svn_stringbuf_t *instructions;
  svn_stringbuf_t *header;
  const svn_string_t *newdata;
  unsigned char ibuf[MAX_INSTRUCTION_LEN], *ip;
  const svn_txdelta_op_t *op;

  /* create the necessary data buffers */
  instructions = svn_stringbuf_create_empty(pool);
  header = svn_stringbuf_create_empty(pool);

  /* Encode the instructions.  */
  for (op = window->ops; op < window->ops + window->num_ops; op++)
    {
      /* Encode the action code and length.  */
      ip = ibuf;
      switch (op->action_code)
        {
        case svn_txdelta_source: *ip = 0; break;
        case svn_txdelta_target: *ip = (0x1 << 6); break;
        case svn_txdelta_new:    *ip = (0x2 << 6); break;
        }
      if (op->length >> 6 == 0)
        *ip++ |= (unsigned char)op->length;
      else
        ip = svn__encode_uint(ip + 1, op->length);
      if (op->action_code != svn_txdelta_new)
        ip = svn__encode_uint(ip, op->offset);
      svn_stringbuf_appendbytes(instructions, (const char *)ibuf, ip - ibuf);
    }

  /* Encode the header.  */
  append_encoded_int(header, window->sview_offset);
  append_encoded_int(header, window->sview_len);
  append_encoded_int(header, window->tview_len);
  if (version == 2)
    {
      svn_stringbuf_t *compressed_instructions;
      compressed_instructions = svn_stringbuf_create_empty(pool);
      SVN_ERR(svn__compress_lz4(instructions->data, instructions->len,
                                compressed_instructions));
      instructions = compressed_instructions;
    }
  else if (version == 1)
    {
      svn_stringbuf_t *compressed_instructions;
      compressed_instructions = svn_stringbuf_create_empty(pool);
      SVN_ERR(svn__compress_zlib(instructions->data, instructions->len,
                                 compressed_instructions, compression_level));
      instructions = compressed_instructions;
    }
  append_encoded_int(header, instructions->len);

  /* Encode the data. */
  if (version == 2)
    {
      svn_stringbuf_t *compressed = svn_stringbuf_create_empty(pool);

      SVN_ERR(svn__compress_lz4(window->new_data->data, window->new_data->len,
                                compressed));
      newdata = svn_stringbuf__morph_into_string(compressed);
    }
  else if (version == 1)
    {
      svn_stringbuf_t *compressed = svn_stringbuf_create_empty(pool);

      SVN_ERR(svn__compress_zlib(window->new_data->data, window->new_data->len,
                                 compressed, compression_level));
      newdata = svn_stringbuf__morph_into_string(compressed);
    }
  else
    newdata = window->new_data;

  append_encoded_int(header, newdata->len);

  *instructions_p = instructions;
  *header_p = header;
  *newdata_p = newdata;

  return SVN_NO_ERROR;
}