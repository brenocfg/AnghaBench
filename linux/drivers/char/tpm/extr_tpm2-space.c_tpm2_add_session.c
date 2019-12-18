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
typedef  scalar_t__ u32 ;
struct tpm_space {scalar_t__* session_tbl; } ;
struct tpm_chip {struct tpm_space work_space; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 

__attribute__((used)) static bool tpm2_add_session(struct tpm_chip *chip, u32 handle)
{
	struct tpm_space *space = &chip->work_space;
	int i;

	for (i = 0; i < ARRAY_SIZE(space->session_tbl); i++)
		if (space->session_tbl[i] == 0)
			break;

	if (i == ARRAY_SIZE(space->session_tbl))
		return false;

	space->session_tbl[i] = handle;
	return true;
}