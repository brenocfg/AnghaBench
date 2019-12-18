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
#define  PIPE_BULK 131 
#define  PIPE_CONTROL 130 
#define  PIPE_INTERRUPT 129 
#define  PIPE_ISOCHRONOUS 128 

__attribute__((used)) static inline char *ed_typestring(int ed_type)
{
	switch (ed_type) {
	case PIPE_CONTROL:
		return "ctrl";
	case PIPE_BULK:
		return "bulk";
	case PIPE_INTERRUPT:
		return "intr";
	case PIPE_ISOCHRONOUS:
		return "isoc";
	}
	return "(bad ed_type)";
}