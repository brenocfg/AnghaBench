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
struct frame_info {int dummy; } ;

/* Variables and functions */
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_frame_register (struct frame_info*,int,char*) ; 

__attribute__((used)) static void
s390_value_to_register (struct frame_info *frame, int regnum,
                        struct type *valtype, const void *in)
{
  char out[8];
  int len = TYPE_LENGTH (valtype);
  gdb_assert (len < 8);

  memset (out, 0, 8);
  memcpy (out, in, len);
  put_frame_register (frame, regnum, out);
}