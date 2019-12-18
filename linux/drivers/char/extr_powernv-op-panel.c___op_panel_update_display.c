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
struct opal_msg {int dummy; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
#define  OPAL_ASYNC_COMPLETION 129 
#define  OPAL_SUCCESS 128 
 int /*<<< orphan*/  num_lines ; 
 int opal_async_get_token_interruptible () ; 
 int /*<<< orphan*/  opal_async_release_token (int) ; 
 int opal_async_wait_response (int,struct opal_msg*) ; 
 int opal_get_async_rc (struct opal_msg) ; 
 int opal_write_oppanel_async (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oppanel_lines ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int __op_panel_update_display(void)
{
	struct opal_msg msg;
	int rc, token;

	token = opal_async_get_token_interruptible();
	if (token < 0) {
		if (token != -ERESTARTSYS)
			pr_debug("Couldn't get OPAL async token [token=%d]\n",
				token);
		return token;
	}

	rc = opal_write_oppanel_async(token, oppanel_lines, num_lines);
	switch (rc) {
	case OPAL_ASYNC_COMPLETION:
		rc = opal_async_wait_response(token, &msg);
		if (rc) {
			pr_debug("Failed to wait for async response [rc=%d]\n",
				rc);
			break;
		}
		rc = opal_get_async_rc(msg);
		if (rc != OPAL_SUCCESS) {
			pr_debug("OPAL async call returned failed [rc=%d]\n",
				rc);
			break;
		}
	case OPAL_SUCCESS:
		break;
	default:
		pr_debug("OPAL write op-panel call failed [rc=%d]\n", rc);
	}

	opal_async_release_token(token);
	return rc;
}