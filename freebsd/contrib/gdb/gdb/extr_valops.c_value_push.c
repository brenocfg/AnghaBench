#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct value {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 scalar_t__ INNER_THAN (int,int) ; 
 int PARM_BOUNDARY ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 int TARGET_CHAR_BIT ; 
 int TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALUE_CONTENTS_ALL (struct value*) ; 
 int /*<<< orphan*/  VALUE_ENCLOSING_TYPE (struct value*) ; 
 int /*<<< orphan*/  write_memory (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static CORE_ADDR
value_push (CORE_ADDR sp, struct value *arg)
{
  int len = TYPE_LENGTH (VALUE_ENCLOSING_TYPE (arg));
  int container_len = len;
  int offset;

  /* How big is the container we're going to put this value in?  */
  if (PARM_BOUNDARY)
    container_len = ((len + PARM_BOUNDARY / TARGET_CHAR_BIT - 1)
		     & ~(PARM_BOUNDARY / TARGET_CHAR_BIT - 1));

  /* Are we going to put it at the high or low end of the container?  */
  if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
    offset = container_len - len;
  else
    offset = 0;

  if (INNER_THAN (1, 2))
    {
      /* stack grows downward */
      sp -= container_len;
      write_memory (sp + offset, VALUE_CONTENTS_ALL (arg), len);
    }
  else
    {
      /* stack grows upward */
      write_memory (sp + offset, VALUE_CONTENTS_ALL (arg), len);
      sp += container_len;
    }

  return sp;
}