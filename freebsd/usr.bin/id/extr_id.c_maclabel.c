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
typedef  int /*<<< orphan*/  mac_t ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mac_free (int /*<<< orphan*/ ) ; 
 int mac_get_proc (int /*<<< orphan*/ ) ; 
 int mac_prepare_process_label (int /*<<< orphan*/ *) ; 
 int mac_to_text (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
maclabel(void)
{
	char *string;
	mac_t label;
	int error;

	error = mac_prepare_process_label(&label);
	if (error == -1)
		errx(1, "mac_prepare_type: %s", strerror(errno));

	error = mac_get_proc(label);
	if (error == -1)
		errx(1, "mac_get_proc: %s", strerror(errno));

	error = mac_to_text(label, &string);
	if (error == -1)
		errx(1, "mac_to_text: %s", strerror(errno));

	(void)printf("%s\n", string);
	mac_free(label);
	free(string);
}