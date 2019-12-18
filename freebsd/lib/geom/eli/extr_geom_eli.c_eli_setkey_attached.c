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
struct gctl_req {int dummy; } ;
struct g_eli_metadata {int md_iterations; } ;
typedef  int /*<<< orphan*/  key ;
typedef  int intmax_t ;

/* Variables and functions */
 int G_ELI_USERKEYLEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * eli_genkey (struct gctl_req*,struct g_eli_metadata*,unsigned char*,int) ; 
 int /*<<< orphan*/  explicit_bzero (unsigned char*,int) ; 
 int gctl_change_param (struct gctl_req*,char*,int,int*) ; 
 int gctl_get_intmax (struct gctl_req*,char*) ; 
 int /*<<< orphan*/  gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,unsigned char*) ; 

__attribute__((used)) static void
eli_setkey_attached(struct gctl_req *req, struct g_eli_metadata *md)
{
	unsigned char key[G_ELI_USERKEYLEN];
	intmax_t val, old = 0;
	int error;

	val = gctl_get_intmax(req, "iterations");
	/* Check if iterations number should be changed. */
	if (val != -1)
		md->md_iterations = val;
	else
		old = md->md_iterations;

	/* Generate key for Master Key encryption. */
	if (eli_genkey(req, md, key, true) == NULL) {
		explicit_bzero(key, sizeof(key));
		return;
	}
	/*
	 * If number of iterations has changed, but wasn't given as a
	 * command-line argument, update the request.
	 */
	if (val == -1 && md->md_iterations != old) {
		error = gctl_change_param(req, "iterations", sizeof(intmax_t),
		    &md->md_iterations);
		assert(error == 0);
	}

	gctl_ro_param(req, "key", sizeof(key), key);
	gctl_issue(req);
	explicit_bzero(key, sizeof(key));
}