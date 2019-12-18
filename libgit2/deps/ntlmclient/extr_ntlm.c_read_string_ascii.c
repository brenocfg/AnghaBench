#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  ntlm_client ;
struct TYPE_3__ {size_t pos; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ ntlm_buf ;

/* Variables and functions */
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntlm_client_set_errmsg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline bool read_string_ascii(
	char **out,
	ntlm_client *ntlm,
	ntlm_buf *message,
	uint8_t string_len)
{
	char *str;

	if ((str = malloc(string_len + 1)) == NULL) {
		ntlm_client_set_errmsg(ntlm, "out of memory");
		return false;
	}

	memcpy(str, &message->buf[message->pos], string_len);
	str[string_len] = '\0';

	message->pos += string_len;

	*out = str;
	return true;
}