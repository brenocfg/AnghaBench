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
typedef  enum mka_created_mode { ____Placeholder_mka_created_mode } mka_created_mode ;

/* Variables and functions */
#define  EAP_EXCHANGE 129 
#define  PSK 128 

__attribute__((used)) static const char * mode_txt(enum mka_created_mode mode)
{
	switch (mode) {
	case PSK:
		return "PSK";
	case EAP_EXCHANGE:
		return "EAP";
	}

	return "?";
}