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
struct sbuf {int dummy; } ;
struct cam_path {int dummy; } ;
typedef  int /*<<< orphan*/  enc_softc_t ;
typedef  int /*<<< orphan*/  enc_element_t ;

/* Variables and functions */
 int /*<<< orphan*/  cam_periph_list (struct cam_path*,struct sbuf*) ; 

__attribute__((used)) static void
ses_elmdevname_callback(enc_softc_t *enc, enc_element_t *elem,
			struct cam_path *path, void *arg)
{
	struct sbuf *sb;

	sb = (struct sbuf *)arg;
	cam_periph_list(path, sb);
}