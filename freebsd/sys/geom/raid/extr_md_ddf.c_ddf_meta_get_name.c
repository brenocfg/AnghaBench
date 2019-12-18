#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ddf_meta {TYPE_2__* vdr; } ;
struct TYPE_4__ {TYPE_1__* entry; } ;
struct TYPE_3__ {char* VD_Name; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static void
ddf_meta_get_name(struct ddf_meta *meta, int num, char *buf)
{
	const char *b;
	int i;

	b = meta->vdr->entry[num].VD_Name;
	for (i = 15; i >= 0; i--)
		if (b[i] != 0x20)
			break;
	memcpy(buf, b, i + 1);
	buf[i + 1] = 0;
}