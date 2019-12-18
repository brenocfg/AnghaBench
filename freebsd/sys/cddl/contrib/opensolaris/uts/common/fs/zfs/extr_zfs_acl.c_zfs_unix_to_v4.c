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
typedef  int uint32_t ;

/* Variables and functions */
 int ACE_EXECUTE ; 
 int ACE_READ_DATA ; 
 int ACE_WRITE_DATA ; 
 int S_IROTH ; 
 int S_IWOTH ; 
 int S_IXOTH ; 

__attribute__((used)) static uint32_t
zfs_unix_to_v4(uint32_t access_mask)
{
	uint32_t new_mask = 0;

	if (access_mask & S_IXOTH)
		new_mask |= ACE_EXECUTE;
	if (access_mask & S_IWOTH)
		new_mask |= ACE_WRITE_DATA;
	if (access_mask & S_IROTH)
		new_mask |= ACE_READ_DATA;
	return (new_mask);
}