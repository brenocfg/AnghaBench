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
 int UART_TAG_BD ; 
 int UART_TAG_BR ; 
 int UART_TAG_CH ; 
 int UART_TAG_DB ; 
 int UART_TAG_DT ; 
 int UART_TAG_IO ; 
 int UART_TAG_MM ; 
 int UART_TAG_PA ; 
 int UART_TAG_RS ; 
 int UART_TAG_SB ; 
 int UART_TAG_XO ; 

__attribute__((used)) static int
uart_parse_tag(const char **p)
{
	int tag;

	if ((*p)[0] == 'b' && (*p)[1] == 'd') {
		tag = UART_TAG_BD;
		goto out;
	}
	if ((*p)[0] == 'b' && (*p)[1] == 'r') {
		tag = UART_TAG_BR;
		goto out;
	}
	if ((*p)[0] == 'c' && (*p)[1] == 'h') {
		tag = UART_TAG_CH;
		goto out;
	}
	if ((*p)[0] == 'd' && (*p)[1] == 'b') {
		tag = UART_TAG_DB;
		goto out;
	}
	if ((*p)[0] == 'd' && (*p)[1] == 't') {
		tag = UART_TAG_DT;
		goto out;
	}
	if ((*p)[0] == 'i' && (*p)[1] == 'o') {
		tag = UART_TAG_IO;
		goto out;
	}
	if ((*p)[0] == 'm' && (*p)[1] == 'm') {
		tag = UART_TAG_MM;
		goto out;
	}
	if ((*p)[0] == 'p' && (*p)[1] == 'a') {
		tag = UART_TAG_PA;
		goto out;
	}
	if ((*p)[0] == 'r' && (*p)[1] == 's') {
		tag = UART_TAG_RS;
		goto out;
	}
	if ((*p)[0] == 's' && (*p)[1] == 'b') {
		tag = UART_TAG_SB;
		goto out;
	}
	if ((*p)[0] == 'x' && (*p)[1] == 'o') {
		tag = UART_TAG_XO;
		goto out;
	}
	return (-1);

out:
	*p += 2;
	if ((*p)[0] != ':')
		return (-1);
	(*p)++;
	return (tag);
}