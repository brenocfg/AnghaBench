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
struct type {int dummy; } ;

/* Variables and functions */
 int TYPE_CODE (struct type const*) ; 
#define  TYPE_CODE_FLT 128 
 int TYPE_LENGTH (struct type const*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 

__attribute__((used)) static int
sparc64_floating_p (const struct type *type)
{
  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_FLT:
      {
	int len = TYPE_LENGTH (type);
	gdb_assert (len == 4 || len == 8 || len == 16);
      }
      return 1;
    default:
      break;
    }

  return 0;
}