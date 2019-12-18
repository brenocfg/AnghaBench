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
typedef  int ControlledDirection ;

/* Variables and functions */
#define  Both 129 
#define  In 128 

__attribute__((used)) static inline const char * ctrl_dir_txt(ControlledDirection dir)
{
	switch (dir) {
	case Both: return "Both";
	case In: return "In";
	default: return "Unknown";
	}
}