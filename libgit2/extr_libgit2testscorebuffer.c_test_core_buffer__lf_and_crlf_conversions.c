#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 char* ALL_CRLF_TEXT_AS_CRLF ; 
 char* ALL_CRLF_TEXT_AS_LF ; 
 char* ALL_CRLF_TEXT_RAW ; 
 char* ALL_LF_TEXT_AS_CRLF ; 
 char* ALL_LF_TEXT_AS_LF ; 
 char* ALL_LF_TEXT_RAW ; 
 TYPE_1__ GIT_BUF_INIT ; 
 char* MORE_CRLF_TEXT_AS_CRLF ; 
 char* MORE_CRLF_TEXT_AS_LF ; 
 char* MORE_CRLF_TEXT_RAW ; 
 char* MORE_LF_TEXT_AS_CRLF ; 
 char* MORE_LF_TEXT_AS_LF ; 
 char* MORE_LF_TEXT_RAW ; 
 int /*<<< orphan*/  check_buf (char*,TYPE_1__) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_buf_text_crlf_to_lf (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_text_lf_to_crlf (TYPE_1__*,TYPE_1__*) ; 

void test_core_buffer__lf_and_crlf_conversions(void)
{
	git_buf src = GIT_BUF_INIT, tgt = GIT_BUF_INIT;

	/* LF source */

	git_buf_sets(&src, "lf\nlf\nlf\nlf\n");

	cl_git_pass(git_buf_text_lf_to_crlf(&tgt, &src));
	check_buf("lf\r\nlf\r\nlf\r\nlf\r\n", tgt);

	cl_git_pass(git_buf_text_crlf_to_lf(&tgt, &src));
	check_buf(src.ptr, tgt);

	git_buf_sets(&src, "\nlf\nlf\nlf\nlf\nlf");

	cl_git_pass(git_buf_text_lf_to_crlf(&tgt, &src));
	check_buf("\r\nlf\r\nlf\r\nlf\r\nlf\r\nlf", tgt);

	cl_git_pass(git_buf_text_crlf_to_lf(&tgt, &src));
	check_buf(src.ptr, tgt);

	/* CRLF source */

	git_buf_sets(&src, "crlf\r\ncrlf\r\ncrlf\r\ncrlf\r\n");

	cl_git_pass(git_buf_text_lf_to_crlf(&tgt, &src));
	check_buf("crlf\r\ncrlf\r\ncrlf\r\ncrlf\r\n", tgt);

	git_buf_sets(&src, "crlf\r\ncrlf\r\ncrlf\r\ncrlf\r\n");

	cl_git_pass(git_buf_text_crlf_to_lf(&tgt, &src));
	check_buf("crlf\ncrlf\ncrlf\ncrlf\n", tgt);

	git_buf_sets(&src, "\r\ncrlf\r\ncrlf\r\ncrlf\r\ncrlf\r\ncrlf");

	cl_git_pass(git_buf_text_lf_to_crlf(&tgt, &src));
	check_buf("\r\ncrlf\r\ncrlf\r\ncrlf\r\ncrlf\r\ncrlf", tgt);

	git_buf_sets(&src, "\r\ncrlf\r\ncrlf\r\ncrlf\r\ncrlf\r\ncrlf");

	cl_git_pass(git_buf_text_crlf_to_lf(&tgt, &src));
	check_buf("\ncrlf\ncrlf\ncrlf\ncrlf\ncrlf", tgt);

	/* CRLF in LF text */

	git_buf_sets(&src, "\nlf\nlf\ncrlf\r\nlf\nlf\ncrlf\r\n");

	cl_git_pass(git_buf_text_lf_to_crlf(&tgt, &src));
	check_buf("\r\nlf\r\nlf\r\ncrlf\r\nlf\r\nlf\r\ncrlf\r\n", tgt);

	git_buf_sets(&src, "\nlf\nlf\ncrlf\r\nlf\nlf\ncrlf\r\n");

	cl_git_pass(git_buf_text_crlf_to_lf(&tgt, &src));
	check_buf("\nlf\nlf\ncrlf\nlf\nlf\ncrlf\n", tgt);

	/* LF in CRLF text */

	git_buf_sets(&src, "\ncrlf\r\ncrlf\r\nlf\ncrlf\r\ncrlf");

	cl_git_pass(git_buf_text_lf_to_crlf(&tgt, &src));
	check_buf("\r\ncrlf\r\ncrlf\r\nlf\r\ncrlf\r\ncrlf", tgt);

	cl_git_pass(git_buf_text_crlf_to_lf(&tgt, &src));
	check_buf("\ncrlf\ncrlf\nlf\ncrlf\ncrlf", tgt);

	/* bare CR test */

	git_buf_sets(&src, "\rcrlf\r\nlf\nlf\ncr\rcrlf\r\nlf\ncr\r");

	cl_git_pass(git_buf_text_lf_to_crlf(&tgt, &src));
	check_buf("\rcrlf\r\nlf\r\nlf\r\ncr\rcrlf\r\nlf\r\ncr\r", tgt);

	git_buf_sets(&src, "\rcrlf\r\nlf\nlf\ncr\rcrlf\r\nlf\ncr\r");

	cl_git_pass(git_buf_text_crlf_to_lf(&tgt, &src));
	check_buf("\rcrlf\nlf\nlf\ncr\rcrlf\nlf\ncr\r", tgt);

	git_buf_sets(&src, "\rcr\r");
	cl_git_pass(git_buf_text_lf_to_crlf(&tgt, &src));
	check_buf(src.ptr, tgt);
	cl_git_pass(git_buf_text_crlf_to_lf(&tgt, &src));
	check_buf("\rcr\r", tgt);

	git_buf_dispose(&src);
	git_buf_dispose(&tgt);

	/* blob correspondence tests */

	git_buf_sets(&src, ALL_CRLF_TEXT_RAW);
	cl_git_pass(git_buf_text_lf_to_crlf(&tgt, &src));
	check_buf(ALL_CRLF_TEXT_AS_CRLF, tgt);
	git_buf_sets(&src, ALL_CRLF_TEXT_RAW);
	cl_git_pass(git_buf_text_crlf_to_lf(&tgt, &src));
	check_buf(ALL_CRLF_TEXT_AS_LF, tgt);
	git_buf_dispose(&src);
	git_buf_dispose(&tgt);

	git_buf_sets(&src, ALL_LF_TEXT_RAW);
	cl_git_pass(git_buf_text_lf_to_crlf(&tgt, &src));
	check_buf(ALL_LF_TEXT_AS_CRLF, tgt);
	git_buf_sets(&src, ALL_LF_TEXT_RAW);
	cl_git_pass(git_buf_text_crlf_to_lf(&tgt, &src));
	check_buf(ALL_LF_TEXT_AS_LF, tgt);
	git_buf_dispose(&src);
	git_buf_dispose(&tgt);

	git_buf_sets(&src, MORE_CRLF_TEXT_RAW);
	cl_git_pass(git_buf_text_lf_to_crlf(&tgt, &src));
	check_buf(MORE_CRLF_TEXT_AS_CRLF, tgt);
	git_buf_sets(&src, MORE_CRLF_TEXT_RAW);
	cl_git_pass(git_buf_text_crlf_to_lf(&tgt, &src));
	check_buf(MORE_CRLF_TEXT_AS_LF, tgt);
	git_buf_dispose(&src);
	git_buf_dispose(&tgt);

	git_buf_sets(&src, MORE_LF_TEXT_RAW);
	cl_git_pass(git_buf_text_lf_to_crlf(&tgt, &src));
	check_buf(MORE_LF_TEXT_AS_CRLF, tgt);
	git_buf_sets(&src, MORE_LF_TEXT_RAW);
	cl_git_pass(git_buf_text_crlf_to_lf(&tgt, &src));
	check_buf(MORE_LF_TEXT_AS_LF, tgt);
	git_buf_dispose(&src);
	git_buf_dispose(&tgt);
}