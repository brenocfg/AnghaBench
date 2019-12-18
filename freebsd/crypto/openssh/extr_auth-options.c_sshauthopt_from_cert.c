#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sshkey {TYPE_1__* cert; int /*<<< orphan*/  type; } ;
struct sshauthopt {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  extensions; int /*<<< orphan*/  critical; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPTIONS_CRITICAL ; 
 int /*<<< orphan*/  OPTIONS_EXTENSIONS ; 
 scalar_t__ SSH2_CERT_TYPE_USER ; 
 int cert_option_list (struct sshauthopt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sshauthopt_free (struct sshauthopt*) ; 
 struct sshauthopt* sshauthopt_new () ; 
 int /*<<< orphan*/  sshkey_type_is_cert (int /*<<< orphan*/ ) ; 

struct sshauthopt *
sshauthopt_from_cert(struct sshkey *k)
{
	struct sshauthopt *ret;

	if (k == NULL || !sshkey_type_is_cert(k->type) || k->cert == NULL ||
	    k->cert->type != SSH2_CERT_TYPE_USER)
		return NULL;

	if ((ret = sshauthopt_new()) == NULL)
		return NULL;

	/* Handle options and critical extensions separately */
	if (cert_option_list(ret, k->cert->critical,
	    OPTIONS_CRITICAL, 1) == -1) {
		sshauthopt_free(ret);
		return NULL;
	}
	if (cert_option_list(ret, k->cert->extensions,
	    OPTIONS_EXTENSIONS, 0) == -1) {
		sshauthopt_free(ret);
		return NULL;
	}
	/* success */
	return ret;
}