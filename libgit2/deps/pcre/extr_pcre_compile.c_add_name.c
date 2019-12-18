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
typedef  scalar_t__ pcre_uchar ;
struct TYPE_3__ {int names_found; int name_entry_size; scalar_t__* name_table; } ;
typedef  TYPE_1__ compile_data ;

/* Variables and functions */
 int IMM2_SIZE ; 
 int /*<<< orphan*/  IN_UCHARS (int) ; 
 int /*<<< orphan*/  PUT2 (scalar_t__*,int /*<<< orphan*/ ,unsigned int) ; 
 int memcmp (scalar_t__ const*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_name(compile_data *cd, const pcre_uchar *name, int length,
  unsigned int groupno)
{
int i;
pcre_uchar *slot = cd->name_table;

for (i = 0; i < cd->names_found; i++)
  {
  int crc = memcmp(name, slot+IMM2_SIZE, IN_UCHARS(length));
  if (crc == 0 && slot[IMM2_SIZE+length] != 0)
    crc = -1; /* Current name is a substring */

  /* Make space in the table and break the loop for an earlier name. For a
  duplicate or later name, carry on. We do this for duplicates so that in the
  simple case (when ?(| is not used) they are in order of their numbers. In all
  cases they are in the order in which they appear in the pattern. */

  if (crc < 0)
    {
    memmove(slot + cd->name_entry_size, slot,
      IN_UCHARS((cd->names_found - i) * cd->name_entry_size));
    break;
    }

  /* Continue the loop for a later or duplicate name */

  slot += cd->name_entry_size;
  }

PUT2(slot, 0, groupno);
memcpy(slot + IMM2_SIZE, name, IN_UCHARS(length));
slot[IMM2_SIZE + length] = 0;
cd->names_found++;
}