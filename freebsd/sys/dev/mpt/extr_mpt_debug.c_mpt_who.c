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

/* Variables and functions */
#define  MPT_DB_INIT_BIOS 133 
#define  MPT_DB_INIT_HOST 132 
#define  MPT_DB_INIT_MANUFACTURE 131 
#define  MPT_DB_INIT_NOONE 130 
#define  MPT_DB_INIT_PCIPEER 129 
#define  MPT_DB_INIT_ROMBIOS 128 

__attribute__((used)) static const char *
mpt_who(int who_init)
{
	const char *who;

	switch (who_init) {
	case MPT_DB_INIT_NOONE:       who = "No One";        break;
	case MPT_DB_INIT_BIOS:        who = "BIOS";          break;
	case MPT_DB_INIT_ROMBIOS:     who = "ROM BIOS";      break;
	case MPT_DB_INIT_PCIPEER:     who = "PCI Peer";      break;
	case MPT_DB_INIT_HOST:        who = "Host Driver";   break;
	case MPT_DB_INIT_MANUFACTURE: who = "Manufacturing"; break;
	default:                      who = "Unknown";       break;
	}
	return who;
}