#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ tview_len; size_t sview_len; TYPE_2__* new_data; scalar_t__ sview_offset; TYPE_1__* ops; } ;
typedef  TYPE_3__ svn_txdelta_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct encoder_baton {int /*<<< orphan*/  output; int /*<<< orphan*/  version; scalar_t__ header_done; } ;
typedef  size_t apr_uint64_t ;
typedef  size_t apr_size_t ;
struct TYPE_6__ {size_t len; char const* data; } ;
struct TYPE_5__ {scalar_t__ action_code; scalar_t__ length; scalar_t__ offset; } ;

/* Variables and functions */
 int MAX_INSTRUCTION_LEN ; 
 int SVNDIFF_HEADER_SIZE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN__MAX_ENCODED_UINT_LEN ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_svndiff_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 unsigned char* svn__encode_uint (unsigned char*,size_t) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ ,char const*,size_t*) ; 
 scalar_t__ svn_txdelta_new ; 

__attribute__((used)) static svn_error_t *
send_simple_insertion_window(svn_txdelta_window_t *window,
                             struct encoder_baton *eb)
{
  unsigned char headers[SVNDIFF_HEADER_SIZE + 5 * SVN__MAX_ENCODED_UINT_LEN
                          + MAX_INSTRUCTION_LEN];
  unsigned char ibuf[MAX_INSTRUCTION_LEN];
  unsigned char *header_current;
  apr_size_t header_len;
  apr_size_t ip_len, i;
  apr_size_t len = window->new_data->len;

  /* there is only one target copy op. It must span the whole window */
  assert(window->ops[0].action_code == svn_txdelta_new);
  assert(window->ops[0].length == window->tview_len);
  assert(window->ops[0].offset == 0);

  /* write stream header if necessary */
  if (!eb->header_done)
    {
      eb->header_done = TRUE;
      memcpy(headers, get_svndiff_header(eb->version), SVNDIFF_HEADER_SIZE);
      header_current = headers + SVNDIFF_HEADER_SIZE;
    }
  else
    {
      header_current = headers;
    }

  /* Encode the action code and length.  */
  if (window->tview_len >> 6 == 0)
    {
      ibuf[0] = (unsigned char)(window->tview_len + (0x2 << 6));
      ip_len = 1;
    }
  else
    {
      ibuf[0] = (0x2 << 6);
      ip_len = svn__encode_uint(ibuf + 1, window->tview_len) - ibuf;
    }

  /* encode the window header.  Please note that the source window may
   * have content despite not being used for deltification. */
  header_current = svn__encode_uint(header_current,
                                    (apr_uint64_t)window->sview_offset);
  header_current = svn__encode_uint(header_current, window->sview_len);
  header_current = svn__encode_uint(header_current, window->tview_len);
  header_current[0] = (unsigned char)ip_len;  /* 1 instruction */
  header_current = svn__encode_uint(&header_current[1], len);

  /* append instructions (1 to a handful of bytes) */
  for (i = 0; i < ip_len; ++i)
    header_current[i] = ibuf[i];

  header_len = header_current - headers + ip_len;

  /* Write out the window.  */
  SVN_ERR(svn_stream_write(eb->output, (const char *)headers, &header_len));
  if (len)
    SVN_ERR(svn_stream_write(eb->output, window->new_data->data, &len));

  return SVN_NO_ERROR;
}