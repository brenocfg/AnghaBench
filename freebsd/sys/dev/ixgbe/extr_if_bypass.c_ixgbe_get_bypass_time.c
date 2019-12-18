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
typedef  int u32 ;
struct timespec {int tv_sec; } ;

/* Variables and functions */
 int SEC_THIS_YEAR (int) ; 
 int /*<<< orphan*/  nanotime (struct timespec*) ; 

__attribute__((used)) static void
ixgbe_get_bypass_time(u32 *year, u32 *sec)
{
	struct timespec current;

	*year = 1970;           /* time starts at 01/01/1970 */
	nanotime(&current);
	*sec = current.tv_sec;

	while(*sec > SEC_THIS_YEAR(*year)) {
		*sec -= SEC_THIS_YEAR(*year);
		(*year)++;
	}
}