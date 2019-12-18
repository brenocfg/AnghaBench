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
typedef  int /*<<< orphan*/  kfile ;
typedef  int /*<<< orphan*/  OpenPGP_key ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  R_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * load_key_file (char*) ; 
 scalar_t__ snprintf (char*,int,char*,char const*,char const*) ; 
 char** trust_store ; 

__attribute__((used)) static OpenPGP_key *
load_trusted_key_id(const char *keyID)
{
	char kfile[MAXPATHLEN];
	const char **tp;
	size_t n;

	for (tp = trust_store; *tp; tp++) {
		n = (size_t)snprintf(kfile, sizeof(kfile), "%s/%s", *tp, keyID);
		if (n >= sizeof(kfile))
			return (NULL);
		if (access(kfile, R_OK) == 0) {
			return (load_key_file(kfile));
		}
	}
	return (NULL);
}