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
struct hdaa_widget {int nconns; scalar_t__* conns; scalar_t__ enable; scalar_t__ bindas; scalar_t__ bindseqmask; scalar_t__ type; int /*<<< orphan*/  param; struct hdaa_devinfo* devinfo; } ;
struct hdaa_devinfo {int dummy; } ;

/* Variables and functions */
 struct hdaa_widget* hdaa_widget_get (struct hdaa_devinfo*,scalar_t__) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
hdaa_audio_adcs_equal(struct hdaa_widget *w1, struct hdaa_widget *w2)
{
	struct hdaa_devinfo *devinfo = w1->devinfo;
	struct hdaa_widget *w3, *w4;
	int i;

	if (memcmp(&w1->param, &w2->param, sizeof(w1->param)))
		return (0);
	if (w1->nconns != 1 || w2->nconns != 1)
		return (0);
	if (w1->conns[0] == w2->conns[0])
		return (1);
	w3 = hdaa_widget_get(devinfo, w1->conns[0]);
	if (w3 == NULL || w3->enable == 0)
		return (0);
	w4 = hdaa_widget_get(devinfo, w2->conns[0]);
	if (w4 == NULL || w4->enable == 0)
		return (0);
	if (w3->bindas == w4->bindas && w3->bindseqmask == w4->bindseqmask)
		return (1);
	if (w4->bindas >= 0)
		return (0);
	if (w3->type != w4->type)
		return (0);
	if (memcmp(&w3->param, &w4->param, sizeof(w3->param)))
		return (0);
	if (w3->nconns != w4->nconns)
		return (0);
	for (i = 0; i < w3->nconns; i++) {
		if (w3->conns[i] != w4->conns[i])
			return (0);
	}
	return (1);
}