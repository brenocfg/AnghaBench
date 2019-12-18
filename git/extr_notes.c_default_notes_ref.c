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
 char* GIT_NOTES_DEFAULT_REF ; 
 int /*<<< orphan*/  GIT_NOTES_REF_ENVIRONMENT ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 char* notes_ref_name ; 

const char *default_notes_ref(void)
{
	const char *notes_ref = NULL;
	if (!notes_ref)
		notes_ref = getenv(GIT_NOTES_REF_ENVIRONMENT);
	if (!notes_ref)
		notes_ref = notes_ref_name; /* value of core.notesRef config */
	if (!notes_ref)
		notes_ref = GIT_NOTES_DEFAULT_REF;
	return notes_ref;
}