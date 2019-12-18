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
 int /*<<< orphan*/ * _cfg ; 
 int /*<<< orphan*/ * _note ; 
 int /*<<< orphan*/ * _repo ; 
 int /*<<< orphan*/ * _sig ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 

void test_notes_notesref__cleanup(void)
{
	git_note_free(_note);
	_note = NULL;

	git_signature_free(_sig);
	_sig = NULL;

	git_config_free(_cfg);
	_cfg = NULL;

	git_repository_free(_repo);
	_repo = NULL;

	cl_fixture_cleanup("testrepo.git");
}