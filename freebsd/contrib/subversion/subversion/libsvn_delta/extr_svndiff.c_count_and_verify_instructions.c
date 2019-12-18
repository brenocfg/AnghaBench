#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ length; int action_code; scalar_t__ offset; } ;
typedef  TYPE_1__ svn_txdelta_op_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_SVNDIFF_INVALID_OPS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 unsigned char* decode_instruction (TYPE_1__*,unsigned char const*,unsigned char const*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
#define  svn_txdelta_new 130 
#define  svn_txdelta_source 129 
#define  svn_txdelta_target 128 

__attribute__((used)) static svn_error_t *
count_and_verify_instructions(int *ninst,
                              const unsigned char *p,
                              const unsigned char *end,
                              apr_size_t sview_len,
                              apr_size_t tview_len,
                              apr_size_t new_len)
{
  int n = 0;
  svn_txdelta_op_t op;
  apr_size_t tpos = 0, npos = 0;

  while (p < end)
    {
      p = decode_instruction(&op, p, end);

      /* Detect any malformed operations from the instruction stream. */
      if (p == NULL)
        return svn_error_createf
          (SVN_ERR_SVNDIFF_INVALID_OPS, NULL,
           _("Invalid diff stream: insn %d cannot be decoded"), n);
      else if (op.length == 0)
        return svn_error_createf
          (SVN_ERR_SVNDIFF_INVALID_OPS, NULL,
           _("Invalid diff stream: insn %d has length zero"), n);
      else if (op.length > tview_len - tpos)
        return svn_error_createf
          (SVN_ERR_SVNDIFF_INVALID_OPS, NULL,
           _("Invalid diff stream: insn %d overflows the target view"), n);

      switch (op.action_code)
        {
        case svn_txdelta_source:
          if (op.length > sview_len - op.offset ||
              op.offset > sview_len)
            return svn_error_createf
              (SVN_ERR_SVNDIFF_INVALID_OPS, NULL,
               _("Invalid diff stream: "
                 "[src] insn %d overflows the source view"), n);
          break;
        case svn_txdelta_target:
          if (op.offset >= tpos)
            return svn_error_createf
              (SVN_ERR_SVNDIFF_INVALID_OPS, NULL,
               _("Invalid diff stream: "
                 "[tgt] insn %d starts beyond the target view position"), n);
          break;
        case svn_txdelta_new:
          if (op.length > new_len - npos)
            return svn_error_createf
              (SVN_ERR_SVNDIFF_INVALID_OPS, NULL,
               _("Invalid diff stream: "
                 "[new] insn %d overflows the new data section"), n);
          npos += op.length;
          break;
        }
      tpos += op.length;
      n++;
    }
  if (tpos != tview_len)
    return svn_error_create(SVN_ERR_SVNDIFF_INVALID_OPS, NULL,
                            _("Delta does not fill the target window"));
  if (npos != new_len)
    return svn_error_create(SVN_ERR_SVNDIFF_INVALID_OPS, NULL,
                            _("Delta does not contain enough new data"));

  *ninst = n;
  return SVN_NO_ERROR;
}