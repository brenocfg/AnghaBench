#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 char* GIT_NOTES_DEFAULT_REF ; 
 int /*<<< orphan*/  _cfg ; 
 int /*<<< orphan*/  _note ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  _sig ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_delete_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_note_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_note_default_ref (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_note_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_note_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_note_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_note_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_now (int /*<<< orphan*/ *,char*,char*) ; 

void test_notes_notesref__config_corenotesref(void)
{
	git_oid oid, note_oid;
	git_buf default_ref = GIT_BUF_INIT;

	cl_git_pass(git_signature_now(&_sig, "alice", "alice@example.com"));
	cl_git_pass(git_oid_fromstr(&oid, "8496071c1b46c854b31185ea97743be6a8774479"));

	cl_git_pass(git_repository_config(&_cfg, _repo));

	cl_git_pass(git_config_set_string(_cfg, "core.notesRef", "refs/notes/mydefaultnotesref"));

	cl_git_pass(git_note_create(&note_oid, _repo, NULL, _sig, _sig, &oid, "test123test\n", 0));

	cl_git_pass(git_note_read(&_note, _repo, NULL, &oid));
	cl_assert_equal_s("test123test\n", git_note_message(_note));
	cl_assert_equal_oid(git_note_id(_note), &note_oid);

	git_note_free(_note);

	cl_git_pass(git_note_read(&_note, _repo, "refs/notes/mydefaultnotesref", &oid));
	cl_assert_equal_s("test123test\n", git_note_message(_note));
	cl_assert_equal_oid(git_note_id(_note), &note_oid);

	cl_git_pass(git_note_default_ref(&default_ref, _repo));
	cl_assert_equal_s("refs/notes/mydefaultnotesref", default_ref.ptr);
	git_buf_clear(&default_ref);

	cl_git_pass(git_config_delete_entry(_cfg, "core.notesRef"));

	cl_git_pass(git_note_default_ref(&default_ref, _repo));
	cl_assert_equal_s(GIT_NOTES_DEFAULT_REF, default_ref.ptr);

	git_buf_dispose(&default_ref);
}