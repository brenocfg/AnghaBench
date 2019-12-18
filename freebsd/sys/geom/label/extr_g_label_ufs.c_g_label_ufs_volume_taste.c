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
struct g_consumer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_LABEL_UFS_VOLUME ; 
 int /*<<< orphan*/  g_label_ufs_taste_common (struct g_consumer*,char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_label_ufs_volume_taste(struct g_consumer *cp, char *label, size_t size)
{

	g_label_ufs_taste_common(cp, label, size, G_LABEL_UFS_VOLUME);
}