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
#define  ENOENT 129 
#define  ENOTDIR 128 

__attribute__((used)) static const char *error_name(int error_number)
{
	switch (error_number) {
	case ENOENT: return "ENOENT";
	case ENOTDIR: return "ENOTDIR";
	default: return "ESOMETHINGELSE";
	}
}