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
struct wpabuf {int dummy; } ;
struct ext_password_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  ext_password_deinit (struct ext_password_data*) ; 
 int /*<<< orphan*/  ext_password_free (struct wpabuf*) ; 
 struct wpabuf* ext_password_get (struct ext_password_data*,char*) ; 
 struct ext_password_data* ext_password_init (char*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ext_password_tests(void)
{
	struct ext_password_data *data;
	int ret = 0;
	struct wpabuf *pw;

	wpa_printf(MSG_INFO, "ext_password tests");

	data = ext_password_init("unknown", "foo");
	if (data != NULL)
		return -1;

	data = ext_password_init("test", NULL);
	if (data == NULL)
		return -1;
	pw = ext_password_get(data, "foo");
	if (pw != NULL)
		ret = -1;
	ext_password_free(pw);

	ext_password_deinit(data);

	pw = ext_password_get(NULL, "foo");
	if (pw != NULL)
		ret = -1;
	ext_password_free(pw);

	return ret;
}