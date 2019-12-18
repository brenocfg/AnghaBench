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
typedef  int /*<<< orphan*/  tOptions ;
typedef  int /*<<< orphan*/  tOptDesc ;

/* Variables and functions */
 int AO_NAME_SIZE ; 
 char NUL ; 
 scalar_t__ find_name (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const* const*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static uintptr_t
find_member_bit(tOptions * opts, tOptDesc * od, char const * pz, int len,
                char const * const * nm_list, unsigned int nm_ct)
{
    char nm_buf[ AO_NAME_SIZE ];

    memcpy(nm_buf, pz, len);
    nm_buf[len] = NUL;

    {
        unsigned int shift_ct = (unsigned int)
            find_name(nm_buf, opts, od, nm_list, nm_ct);
        if (shift_ct >= nm_ct)
            return 0UL;

        return (uintptr_t)1U << shift_ct;
    }
}