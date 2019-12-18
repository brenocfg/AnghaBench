#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_1__ ;

/* Type definitions */
struct TYPE_47__ {int id; } ;
typedef  TYPE_1__ tokenstr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  AUT_ARG32 170 
#define  AUT_ARG64 169 
#define  AUT_ATTR32 168 
#define  AUT_ATTR64 167 
#define  AUT_DATA 166 
#define  AUT_EXEC_ARGS 165 
#define  AUT_EXEC_ENV 164 
#define  AUT_EXIT 163 
#define  AUT_HEADER32 162 
#define  AUT_HEADER32_EX 161 
#define  AUT_HEADER64 160 
#define  AUT_HEADER64_EX 159 
#define  AUT_IN_ADDR 158 
#define  AUT_IN_ADDR_EX 157 
#define  AUT_IP 156 
#define  AUT_IPC 155 
#define  AUT_IPC_PERM 154 
#define  AUT_IPORT 153 
#define  AUT_NEWGROUPS 152 
#define  AUT_OPAQUE 151 
#define  AUT_OTHER_FILE32 150 
#define  AUT_PATH 149 
#define  AUT_PRIV 148 
#define  AUT_PROCESS32 147 
#define  AUT_PROCESS32_EX 146 
#define  AUT_PROCESS64 145 
#define  AUT_PROCESS64_EX 144 
#define  AUT_RETURN32 143 
#define  AUT_RETURN64 142 
#define  AUT_SEQ 141 
#define  AUT_SOCKET 140 
#define  AUT_SOCKET_EX 139 
#define  AUT_SOCKINET128 138 
#define  AUT_SOCKINET32 137 
#define  AUT_SOCKUNIX 136 
#define  AUT_SUBJECT32 135 
#define  AUT_SUBJECT32_EX 134 
#define  AUT_SUBJECT64 133 
#define  AUT_SUBJECT64_EX 132 
#define  AUT_TEXT 131 
#define  AUT_TRAILER 130 
#define  AUT_UPRIV 129 
#define  AUT_ZONENAME 128 
 int /*<<< orphan*/  print_arb_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_arg32_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_arg64_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_attr32_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_attr64_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_execarg_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_execenv_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_exit_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_file_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_header32_ex_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_header32_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_header64_ex_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_header64_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_inaddr_ex_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_inaddr_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_invalid_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_ip_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_ipc_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_ipcperm_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_iport_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_newgroups_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_opaque_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_path_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_privset_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_process32_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_process32ex_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_process64_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_process64ex_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_return32_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_return64_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_seq_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_sock_inet128_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_sock_inet32_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_sock_unix_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_socket_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_socketex32_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_subject32_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_subject32ex_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_subject64_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_subject64ex_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_text_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_trailer_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_upriv_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  print_zonename_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 

void
au_print_flags_tok(FILE *outfp, tokenstr_t *tok, char *del, int oflags)
{

	switch(tok->id) {
	case AUT_HEADER32:
		print_header32_tok(outfp, tok, del, oflags);
		return;

	case AUT_HEADER32_EX:
		print_header32_ex_tok(outfp, tok, del, oflags);
		return;

	case AUT_HEADER64:
		print_header64_tok(outfp, tok, del, oflags);
		return;

	case AUT_HEADER64_EX:
		print_header64_ex_tok(outfp, tok, del, oflags);
		return;

	case AUT_TRAILER:
		print_trailer_tok(outfp, tok, del, oflags);
		return;

	case AUT_ARG32:
		print_arg32_tok(outfp, tok, del, oflags);
		return;

	case AUT_ARG64:
		print_arg64_tok(outfp, tok, del, oflags);
		return;

	case AUT_DATA:
		print_arb_tok(outfp, tok, del, oflags);
		return;

	case AUT_ATTR32:
		print_attr32_tok(outfp, tok, del, oflags);
		return;

	case AUT_ATTR64:
		print_attr64_tok(outfp, tok, del, oflags);
		return;

	case AUT_EXIT:
		print_exit_tok(outfp, tok, del, oflags);
		return;

	case AUT_EXEC_ARGS:
		print_execarg_tok(outfp, tok, del, oflags);
		return;

	case AUT_EXEC_ENV:
		print_execenv_tok(outfp, tok, del, oflags);
		return;

	case AUT_OTHER_FILE32:
		print_file_tok(outfp, tok, del, oflags);
		return;

	case AUT_NEWGROUPS:
		print_newgroups_tok(outfp, tok, del, oflags);
		return;

	case AUT_IN_ADDR:
		print_inaddr_tok(outfp, tok, del, oflags);
		return;

	case AUT_IN_ADDR_EX:
		print_inaddr_ex_tok(outfp, tok, del, oflags);
		return;

	case AUT_IP:
		print_ip_tok(outfp, tok, del, oflags);
		return;

	case AUT_IPC:
		print_ipc_tok(outfp, tok, del, oflags);
		return;

	case AUT_IPC_PERM:
		print_ipcperm_tok(outfp, tok, del, oflags);
		return;

	case AUT_IPORT:
		print_iport_tok(outfp, tok, del, oflags);
		return;

	case AUT_OPAQUE:
		print_opaque_tok(outfp, tok, del, oflags);
		return;

	case AUT_PATH:
		print_path_tok(outfp, tok, del, oflags);
		return;

	case AUT_PROCESS32:
		print_process32_tok(outfp, tok, del, oflags);
		return;

	case AUT_PROCESS32_EX:
		print_process32ex_tok(outfp, tok, del, oflags);
		return;

	case AUT_PROCESS64:
		print_process64_tok(outfp, tok, del, oflags);
		return;

	case AUT_PROCESS64_EX:
		print_process64ex_tok(outfp, tok, del, oflags);
		return;

	case AUT_RETURN32:
		print_return32_tok(outfp, tok, del, oflags);
		return;

	case AUT_RETURN64:
		print_return64_tok(outfp, tok, del, oflags);
		return;

	case AUT_SEQ:
		print_seq_tok(outfp, tok, del, oflags);
		return;

	case AUT_SOCKET:
		print_socket_tok(outfp, tok, del, oflags);
		return;

	case AUT_SOCKINET32:
		print_sock_inet32_tok(outfp, tok, del, oflags);
		return;

	case AUT_SOCKUNIX:
		print_sock_unix_tok(outfp, tok, del, oflags);
		return;

	case AUT_SOCKINET128:
		print_sock_inet128_tok(outfp, tok, del, oflags);
		return;

	case AUT_SUBJECT32:
		print_subject32_tok(outfp, tok, del, oflags);
		return;

	case AUT_SUBJECT64:
		print_subject64_tok(outfp, tok, del, oflags);
		return;

	case AUT_SUBJECT32_EX:
		print_subject32ex_tok(outfp, tok, del, oflags);
		return;

	case AUT_SUBJECT64_EX:
		print_subject64ex_tok(outfp, tok, del, oflags);
		return;

	case AUT_TEXT:
		print_text_tok(outfp, tok, del, oflags);
		return;

	case AUT_SOCKET_EX:
		print_socketex32_tok(outfp, tok, del, oflags);
		return;

	case AUT_ZONENAME:
		print_zonename_tok(outfp, tok, del, oflags);
		return;

	case AUT_UPRIV:
		print_upriv_tok(outfp, tok, del, oflags);
		return;

	case  AUT_PRIV:
		print_privset_tok(outfp, tok, del, oflags);
		return;

	default:
		print_invalid_tok(outfp, tok, del, oflags);
	}
}