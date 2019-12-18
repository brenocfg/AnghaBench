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
typedef  int u_char ;
struct TYPE_47__ {int len; int* data; int id; } ;
typedef  TYPE_1__ tokenstr_t ;

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
 int fetch_arb_tok (TYPE_1__*,int*,int) ; 
 int fetch_arg32_tok (TYPE_1__*,int*,int) ; 
 int fetch_arg64_tok (TYPE_1__*,int*,int) ; 
 int fetch_attr32_tok (TYPE_1__*,int*,int) ; 
 int fetch_attr64_tok (TYPE_1__*,int*,int) ; 
 int fetch_execarg_tok (TYPE_1__*,int*,int) ; 
 int fetch_execenv_tok (TYPE_1__*,int*,int) ; 
 int fetch_exit_tok (TYPE_1__*,int*,int) ; 
 int fetch_file_tok (TYPE_1__*,int*,int) ; 
 int fetch_header32_ex_tok (TYPE_1__*,int*,int) ; 
 int fetch_header32_tok (TYPE_1__*,int*,int) ; 
 int fetch_header64_ex_tok (TYPE_1__*,int*,int) ; 
 int fetch_header64_tok (TYPE_1__*,int*,int) ; 
 int fetch_inaddr_ex_tok (TYPE_1__*,int*,int) ; 
 int fetch_inaddr_tok (TYPE_1__*,int*,int) ; 
 int fetch_invalid_tok (TYPE_1__*,int*,int) ; 
 int fetch_ip_tok (TYPE_1__*,int*,int) ; 
 int fetch_ipc_tok (TYPE_1__*,int*,int) ; 
 int fetch_ipcperm_tok (TYPE_1__*,int*,int) ; 
 int fetch_iport_tok (TYPE_1__*,int*,int) ; 
 int fetch_newgroups_tok (TYPE_1__*,int*,int) ; 
 int fetch_opaque_tok (TYPE_1__*,int*,int) ; 
 int fetch_path_tok (TYPE_1__*,int*,int) ; 
 int fetch_priv_tok (TYPE_1__*,int*,int) ; 
 int fetch_privset_tok (TYPE_1__*,int*,int) ; 
 int fetch_process32_tok (TYPE_1__*,int*,int) ; 
 int fetch_process32ex_tok (TYPE_1__*,int*,int) ; 
 int fetch_process64_tok (TYPE_1__*,int*,int) ; 
 int fetch_process64ex_tok (TYPE_1__*,int*,int) ; 
 int fetch_return32_tok (TYPE_1__*,int*,int) ; 
 int fetch_return64_tok (TYPE_1__*,int*,int) ; 
 int fetch_seq_tok (TYPE_1__*,int*,int) ; 
 int fetch_sock_inet128_tok (TYPE_1__*,int*,int) ; 
 int fetch_sock_inet32_tok (TYPE_1__*,int*,int) ; 
 int fetch_sock_unix_tok (TYPE_1__*,int*,int) ; 
 int fetch_socket_tok (TYPE_1__*,int*,int) ; 
 int fetch_socketex32_tok (TYPE_1__*,int*,int) ; 
 int fetch_subject32_tok (TYPE_1__*,int*,int) ; 
 int fetch_subject32ex_tok (TYPE_1__*,int*,int) ; 
 int fetch_subject64_tok (TYPE_1__*,int*,int) ; 
 int fetch_subject64ex_tok (TYPE_1__*,int*,int) ; 
 int fetch_text_tok (TYPE_1__*,int*,int) ; 
 int fetch_trailer_tok (TYPE_1__*,int*,int) ; 
 int fetch_zonename_tok (TYPE_1__*,int*,int) ; 

int
au_fetch_tok(tokenstr_t *tok, u_char *buf, int len)
{

	if (len <= 0)
		return (-1);

	tok->len = 1;
	tok->data = buf;
	tok->id = *buf;

	switch(tok->id) {
	case AUT_HEADER32:
		return (fetch_header32_tok(tok, buf, len));

	case AUT_HEADER32_EX:
		return (fetch_header32_ex_tok(tok, buf, len));

	case AUT_HEADER64:
		return (fetch_header64_tok(tok, buf, len));

	case AUT_HEADER64_EX:
		return (fetch_header64_ex_tok(tok, buf, len));

	case AUT_TRAILER:
		return (fetch_trailer_tok(tok, buf, len));

	case AUT_ARG32:
		return (fetch_arg32_tok(tok, buf, len));

	case AUT_ARG64:
		return (fetch_arg64_tok(tok, buf, len));

	case AUT_ATTR32:
		return (fetch_attr32_tok(tok, buf, len));

	case AUT_ATTR64:
		return (fetch_attr64_tok(tok, buf, len));

	case AUT_EXIT:
		return (fetch_exit_tok(tok, buf, len));

	case AUT_EXEC_ARGS:
		return (fetch_execarg_tok(tok, buf, len));

	case AUT_EXEC_ENV:
		return (fetch_execenv_tok(tok, buf, len));

	case AUT_OTHER_FILE32:
		return (fetch_file_tok(tok, buf, len));

	case AUT_NEWGROUPS:
		return (fetch_newgroups_tok(tok, buf, len));

	case AUT_IN_ADDR:
		return (fetch_inaddr_tok(tok, buf, len));

	case AUT_IN_ADDR_EX:
		return (fetch_inaddr_ex_tok(tok, buf, len));

	case AUT_IP:
		return (fetch_ip_tok(tok, buf, len));

	case AUT_IPC:
		return (fetch_ipc_tok(tok, buf, len));

	case AUT_IPC_PERM:
		return (fetch_ipcperm_tok(tok, buf, len));

	case AUT_IPORT:
		return (fetch_iport_tok(tok, buf, len));

	case AUT_OPAQUE:
		return (fetch_opaque_tok(tok, buf, len));

	case AUT_PATH:
		return (fetch_path_tok(tok, buf, len));

	case AUT_PROCESS32:
		return (fetch_process32_tok(tok, buf, len));

	case AUT_PROCESS32_EX:
		return (fetch_process32ex_tok(tok, buf, len));

	case AUT_PROCESS64:
		return (fetch_process64_tok(tok, buf, len));

	case AUT_PROCESS64_EX:
		return (fetch_process64ex_tok(tok, buf, len));

	case AUT_RETURN32:
		return (fetch_return32_tok(tok, buf, len));

	case AUT_RETURN64:
		return (fetch_return64_tok(tok, buf, len));

	case AUT_SEQ:
		return (fetch_seq_tok(tok, buf, len));

	case AUT_SOCKET:
		return (fetch_socket_tok(tok, buf, len));

	case AUT_SOCKINET32:
		return (fetch_sock_inet32_tok(tok, buf, len));

	case AUT_SOCKUNIX:
		return (fetch_sock_unix_tok(tok, buf, len));

	case AUT_SOCKINET128:
		return (fetch_sock_inet128_tok(tok, buf, len));

	case AUT_SUBJECT32:
		return (fetch_subject32_tok(tok, buf, len));

	case AUT_SUBJECT32_EX:
		return (fetch_subject32ex_tok(tok, buf, len));

	case AUT_SUBJECT64:
		return (fetch_subject64_tok(tok, buf, len));

	case AUT_SUBJECT64_EX:
		return (fetch_subject64ex_tok(tok, buf, len));

	case AUT_TEXT:
		return (fetch_text_tok(tok, buf, len));

	case AUT_SOCKET_EX:
		return (fetch_socketex32_tok(tok, buf, len));

	case AUT_DATA:
		return (fetch_arb_tok(tok, buf, len));

	case AUT_ZONENAME:
		return (fetch_zonename_tok(tok, buf, len));

	case AUT_UPRIV:
		return (fetch_priv_tok(tok, buf, len));

	case AUT_PRIV:
		return (fetch_privset_tok(tok, buf, len));

	default:
		return (fetch_invalid_tok(tok, buf, len));
	}
}