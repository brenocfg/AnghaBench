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
typedef  int DWORD ;

/* Variables and functions */
#define  ERROR_ACCESS_DENIED 129 
#define  ERROR_SHARING_VIOLATION 128 

__attribute__((used)) static inline int is_file_in_use_error(DWORD errcode)
{
	switch (errcode) {
	case ERROR_SHARING_VIOLATION:
	case ERROR_ACCESS_DENIED:
		return 1;
	}

	return 0;
}