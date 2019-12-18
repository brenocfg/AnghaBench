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
typedef  int /*<<< orphan*/  name_table ;

/* Variables and functions */
#define  KB_101 130 
#define  KB_84 129 
#define  KB_OTHER 128 

__attribute__((used)) static const char *
get_kbd_type_name(int type)
{
	static struct {
		int type;
		const char *name;
	} name_table[] = {
		{ KB_84,	"AT 84" },
		{ KB_101,	"AT 101/102" },
		{ KB_OTHER,	"generic" },
	};
	unsigned int i;

	for (i = 0; i < sizeof(name_table)/sizeof(name_table[0]); ++i) {
		if (type == name_table[i].type)
			return name_table[i].name;
	}
	return "unknown";
}