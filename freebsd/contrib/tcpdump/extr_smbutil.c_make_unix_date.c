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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_LE_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  int_unix_date (int /*<<< orphan*/ ) ; 

__attribute__((used)) static time_t
make_unix_date(const u_char *date_ptr)
{
    uint32_t dos_date = 0;

    dos_date = EXTRACT_LE_32BITS(date_ptr);

    return int_unix_date(dos_date);
}