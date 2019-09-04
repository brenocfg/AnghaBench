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
struct index_state {int dummy; } ;
struct conv_attrs {void* crlf_action; void* attr_action; int /*<<< orphan*/  working_tree_encoding; int /*<<< orphan*/  drv; int /*<<< orphan*/  ident; } ;
struct attr_check_item {int dummy; } ;
struct attr_check {struct attr_check_item* items; } ;
typedef  enum eol { ____Placeholder_eol } eol ;

/* Variables and functions */
 scalar_t__ AUTO_CRLF_FALSE ; 
 scalar_t__ AUTO_CRLF_INPUT ; 
 scalar_t__ AUTO_CRLF_TRUE ; 
 void* CRLF_AUTO ; 
 void* CRLF_AUTO_CRLF ; 
 void* CRLF_AUTO_INPUT ; 
 void* CRLF_BINARY ; 
 void* CRLF_TEXT ; 
 void* CRLF_TEXT_CRLF ; 
 void* CRLF_TEXT_INPUT ; 
 void* CRLF_UNDEFINED ; 
 int EOL_CRLF ; 
 int EOL_LF ; 
 struct attr_check* attr_check_initl (char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ auto_crlf ; 
 int /*<<< orphan*/  git_check_attr (struct index_state const*,char const*,struct attr_check*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_check_convert (struct attr_check_item*) ; 
 void* git_path_check_crlf (struct attr_check_item*) ; 
 int /*<<< orphan*/  git_path_check_encoding (struct attr_check_item*) ; 
 int git_path_check_eol (struct attr_check_item*) ; 
 int /*<<< orphan*/  git_path_check_ident (struct attr_check_item*) ; 
 int /*<<< orphan*/  read_convert_config ; 
 scalar_t__ text_eol_is_crlf () ; 
 int /*<<< orphan*/  user_convert ; 
 int /*<<< orphan*/ * user_convert_tail ; 

__attribute__((used)) static void convert_attrs(const struct index_state *istate,
			  struct conv_attrs *ca, const char *path)
{
	static struct attr_check *check;
	struct attr_check_item *ccheck = NULL;

	if (!check) {
		check = attr_check_initl("crlf", "ident", "filter",
					 "eol", "text", "working-tree-encoding",
					 NULL);
		user_convert_tail = &user_convert;
		git_config(read_convert_config, NULL);
	}

	git_check_attr(istate, path, check);
	ccheck = check->items;
	ca->crlf_action = git_path_check_crlf(ccheck + 4);
	if (ca->crlf_action == CRLF_UNDEFINED)
		ca->crlf_action = git_path_check_crlf(ccheck + 0);
	ca->ident = git_path_check_ident(ccheck + 1);
	ca->drv = git_path_check_convert(ccheck + 2);
	if (ca->crlf_action != CRLF_BINARY) {
		enum eol eol_attr = git_path_check_eol(ccheck + 3);
		if (ca->crlf_action == CRLF_AUTO && eol_attr == EOL_LF)
			ca->crlf_action = CRLF_AUTO_INPUT;
		else if (ca->crlf_action == CRLF_AUTO && eol_attr == EOL_CRLF)
			ca->crlf_action = CRLF_AUTO_CRLF;
		else if (eol_attr == EOL_LF)
			ca->crlf_action = CRLF_TEXT_INPUT;
		else if (eol_attr == EOL_CRLF)
			ca->crlf_action = CRLF_TEXT_CRLF;
	}
	ca->working_tree_encoding = git_path_check_encoding(ccheck + 5);

	/* Save attr and make a decision for action */
	ca->attr_action = ca->crlf_action;
	if (ca->crlf_action == CRLF_TEXT)
		ca->crlf_action = text_eol_is_crlf() ? CRLF_TEXT_CRLF : CRLF_TEXT_INPUT;
	if (ca->crlf_action == CRLF_UNDEFINED && auto_crlf == AUTO_CRLF_FALSE)
		ca->crlf_action = CRLF_BINARY;
	if (ca->crlf_action == CRLF_UNDEFINED && auto_crlf == AUTO_CRLF_TRUE)
		ca->crlf_action = CRLF_AUTO_CRLF;
	if (ca->crlf_action == CRLF_UNDEFINED && auto_crlf == AUTO_CRLF_INPUT)
		ca->crlf_action = CRLF_AUTO_INPUT;
}