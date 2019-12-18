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
typedef  int u_char ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  AUT_ARG32 167 
#define  AUT_ARG64 166 
#define  AUT_ATTR32 165 
#define  AUT_ATTR64 164 
#define  AUT_DATA 163 
#define  AUT_EXEC_ARGS 162 
#define  AUT_EXEC_ENV 161 
#define  AUT_EXIT 160 
#define  AUT_HEADER32 159 
#define  AUT_HEADER32_EX 158 
#define  AUT_HEADER64 157 
#define  AUT_HEADER64_EX 156 
#define  AUT_IN_ADDR 155 
#define  AUT_IN_ADDR_EX 154 
#define  AUT_IP 153 
#define  AUT_IPC 152 
#define  AUT_IPC_PERM 151 
#define  AUT_IPORT 150 
#define  AUT_NEWGROUPS 149 
#define  AUT_OPAQUE 148 
#define  AUT_OTHER_FILE32 147 
#define  AUT_PATH 146 
#define  AUT_PROCESS32 145 
#define  AUT_PROCESS32_EX 144 
#define  AUT_PROCESS64 143 
#define  AUT_PROCESS64_EX 142 
#define  AUT_RETURN32 141 
#define  AUT_RETURN64 140 
#define  AUT_SEQ 139 
#define  AUT_SOCKET 138 
#define  AUT_SOCKET_EX 137 
#define  AUT_SOCKINET128 136 
#define  AUT_SOCKINET32 135 
#define  AUT_SOCKUNIX 134 
#define  AUT_SUBJECT32 133 
#define  AUT_SUBJECT32_EX 132 
#define  AUT_SUBJECT64 131 
#define  AUT_SUBJECT64_EX 130 
#define  AUT_TEXT 129 
#define  AUT_ZONENAME 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
close_tag(FILE *fp, u_char type)
{

	switch(type) {
	case AUT_HEADER32:
		fprintf(fp, ">");
		break;

	case AUT_HEADER32_EX:
		fprintf(fp, ">");
		break;

	case AUT_HEADER64:
		fprintf(fp, ">");
		break;

	case AUT_HEADER64_EX:
		fprintf(fp, ">");
		break;

	case AUT_ARG32:
		fprintf(fp, "/>");
		break;

	case AUT_ARG64:
		fprintf(fp, "/>");
		break;

	case AUT_ATTR32:
		fprintf(fp, "/>");
		break;

	case AUT_ATTR64:
		fprintf(fp, "/>");
		break;

	case AUT_EXIT:
		fprintf(fp, "/>");
		break;

	case AUT_EXEC_ARGS:
		fprintf(fp, "</exec_args>");
		break;

	case AUT_EXEC_ENV:
		fprintf(fp, "</exec_env>");
		break;

	case AUT_OTHER_FILE32:
		fprintf(fp, "</file>");
		break;

	case AUT_NEWGROUPS:
		fprintf(fp, "</group>");
		break;

	case AUT_IN_ADDR:
		fprintf(fp, "</ip_address>");
		break;

	case AUT_IN_ADDR_EX:
		fprintf(fp, "</ip_address>");
		break;

	case AUT_IP:
		fprintf(fp, "/>");
		break;

	case AUT_IPC:
		fprintf(fp, "/>");
		break;

	case AUT_IPC_PERM:
		fprintf(fp, "/>");
		break;

	case AUT_IPORT:
		fprintf(fp, "</ip_port>");
		break;

	case AUT_OPAQUE:
		fprintf(fp, "</opaque>");
		break;

	case AUT_PATH:
		fprintf(fp, "</path>");
		break;

	case AUT_PROCESS32:
		fprintf(fp, "/>");
		break;

	case AUT_PROCESS32_EX:
		fprintf(fp, "/>");
		break;

	case AUT_PROCESS64:
		fprintf(fp, "/>");
		break;

	case AUT_PROCESS64_EX:
		fprintf(fp, "/>");
		break;

	case AUT_RETURN32:
		fprintf(fp, "/>");
		break;

	case AUT_RETURN64:
		fprintf(fp, "/>");
		break;

	case AUT_SEQ:
		fprintf(fp, "/>");
		break;

	case AUT_SOCKET:
		fprintf(fp, "/>");
		break;

	case AUT_SOCKINET32:
		fprintf(fp, "/>");
		break;

	case AUT_SOCKUNIX:
		fprintf(fp, "/>");
		break;

	case AUT_SOCKINET128:
		fprintf(fp, "/>");
		break;

	case AUT_SUBJECT32:
		fprintf(fp, "/>");
		break;

	case AUT_SUBJECT64:
		fprintf(fp, "/>");
		break;

	case AUT_SUBJECT32_EX:
		fprintf(fp, "/>");
		break;

	case AUT_SUBJECT64_EX:
		fprintf(fp, "/>");
		break;

	case AUT_TEXT:
		fprintf(fp, "</text>");
		break;

	case AUT_SOCKET_EX:
		fprintf(fp, "/>");
		break;

	case AUT_DATA:
		fprintf(fp, "</arbitrary>");
		break;

	case AUT_ZONENAME:
		fprintf(fp, "/>");
		break;
	}
}