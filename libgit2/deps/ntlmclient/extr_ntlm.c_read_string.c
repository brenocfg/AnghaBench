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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ntlm_client ;
typedef  int /*<<< orphan*/  ntlm_buf ;

/* Variables and functions */
 int read_string_ascii (char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int read_string_unicode (char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool read_string(
	char **out,
	ntlm_client *ntlm,
	ntlm_buf *message,
	uint8_t string_len,
	bool unicode)
{
	if (unicode)
		return read_string_unicode(out, ntlm, message, string_len);
	else
		return read_string_ascii(out, ntlm, message, string_len);
}