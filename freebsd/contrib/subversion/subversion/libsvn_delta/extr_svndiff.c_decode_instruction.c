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
struct TYPE_3__ {int action_code; int length; int offset; } ;
typedef  TYPE_1__ svn_txdelta_op_t ;
typedef  enum svn_delta_action { ____Placeholder_svn_delta_action } svn_delta_action ;
typedef  int apr_size_t ;

/* Variables and functions */
 unsigned char* decode_size (int*,unsigned char const*,unsigned char const*) ; 
 int svn_txdelta_new ; 

__attribute__((used)) static const unsigned char *
decode_instruction(svn_txdelta_op_t *op,
                   const unsigned char *p,
                   const unsigned char *end)
{
  apr_size_t c;
  apr_size_t action;

  if (p == end)
    return NULL;

  /* We need this more than once */
  c = *p++;

  /* Decode the instruction selector.  */
  action = (c >> 6) & 0x3;
  if (action >= 0x3)
      return NULL;

  /* This relies on enum svn_delta_action values to match and never to be
     redefined. */
  op->action_code = (enum svn_delta_action)(action);

  /* Decode the length and offset.  */
  op->length = c & 0x3f;
  if (op->length == 0)
    {
      p = decode_size(&op->length, p, end);
      if (p == NULL)
        return NULL;
    }
  if (action != svn_txdelta_new)
    {
      p = decode_size(&op->offset, p, end);
      if (p == NULL)
        return NULL;
    }

  return p;
}