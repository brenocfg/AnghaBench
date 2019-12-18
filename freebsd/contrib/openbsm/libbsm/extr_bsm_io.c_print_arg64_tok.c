#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  text; int /*<<< orphan*/  val; int /*<<< orphan*/  no; } ;
struct TYPE_6__ {TYPE_1__ arg64; } ;
struct TYPE_7__ {TYPE_2__ tt; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ tokenstr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AU_OFLAG_XML ; 
 int /*<<< orphan*/  close_attr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_attr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_1_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_8_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_delim (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_tok_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
print_arg64_tok(FILE *fp, tokenstr_t *tok, char *del, int oflags)
{

	print_tok_type(fp, tok->id, "argument", oflags);
	if (oflags & AU_OFLAG_XML) {
		open_attr(fp, "arg-num");
		print_1_byte(fp, tok->tt.arg64.no, "%u");
		close_attr(fp);
		open_attr(fp, "value");
		print_8_bytes(fp, tok->tt.arg64.val, "0x%llx");
		close_attr(fp);
		open_attr(fp, "desc");
		print_string(fp, tok->tt.arg64.text, tok->tt.arg64.len);
		close_attr(fp);
		close_tag(fp, tok->id);
	} else {
		print_delim(fp, del);
		print_1_byte(fp, tok->tt.arg64.no, "%u");
		print_delim(fp, del);
		print_8_bytes(fp, tok->tt.arg64.val, "0x%llx");
		print_delim(fp, del);
		print_string(fp, tok->tt.arg64.text, tok->tt.arg64.len);
	}
}