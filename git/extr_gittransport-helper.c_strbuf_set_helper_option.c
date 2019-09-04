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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct helper_data {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ recvline (struct helper_data*,struct strbuf*) ; 
 int /*<<< orphan*/  sendline (struct helper_data*,struct strbuf*) ; 
 scalar_t__ starts_with (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int strbuf_set_helper_option(struct helper_data *data,
				    struct strbuf *buf)
{
	int ret;

	sendline(data, buf);
	if (recvline(data, buf))
		exit(128);

	if (!strcmp(buf->buf, "ok"))
		ret = 0;
	else if (starts_with(buf->buf, "error"))
		ret = -1;
	else if (!strcmp(buf->buf, "unsupported"))
		ret = 1;
	else {
		warning(_("%s unexpectedly said: '%s'"), data->name, buf->buf);
		ret = 1;
	}
	return ret;
}