#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  vtable; } ;
typedef  TYPE_1__ br_hash_compat_context ;
struct TYPE_5__ {int /*<<< orphan*/  (* out ) (int /*<<< orphan*/ *,unsigned char*) ;int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ br_hash_class ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int EPERM ; 
 scalar_t__ MAXPATHLEN ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VEF_VERBOSE ; 
 int VE_FINGERPRINT_WRONG ; 
 int VE_NOT_CHECKED ; 
 int VE_VERIFIED ; 
 int /*<<< orphan*/  add_verify_status (struct stat*,int) ; 
 int br_sha256_SIZE ; 
 TYPE_2__ br_sha256_vtable ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hexdigest (char*,int,unsigned char*,int) ; 
 int is_verified (struct stat*) ; 
 char* manifest_hash ; 
 char* manifest_path ; 
 char* manifest_prefix ; 
 int manifest_present ; 
 char* read_file (char const*,int /*<<< orphan*/ *) ; 
 int stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strnlen (char const*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,unsigned char*) ; 
 scalar_t__ verify_signed (char const*,int /*<<< orphan*/ ) ; 

int
pass_manifest(const char *path, const char *prefix)
{
	char *content;
	struct stat st;
	unsigned char digest[br_sha256_SIZE];
	const br_hash_class *md;
	br_hash_compat_context ctx;
	int rc;

	content = NULL;
	md = &br_sha256_vtable;

	if (strnlen(path, MAXPATHLEN) == MAXPATHLEN ||
	    strnlen(prefix, MAXPATHLEN) == MAXPATHLEN)
		return (EINVAL);

	rc = stat(path, &st);
	if (rc != 0)
		goto out;

	if (!S_ISREG(st.st_mode)) {
		rc = EINVAL;
		goto out;
	}

	rc = is_verified(&st);

	if (rc != VE_NOT_CHECKED && rc != VE_VERIFIED) {
		rc = EPERM;
		goto out;
	}

	if (rc == VE_VERIFIED)
		content = read_file(path, NULL);
	else
		content = (char *)verify_signed(path, VEF_VERBOSE);

	if (content == NULL) {
		add_verify_status(&st, VE_FINGERPRINT_WRONG);
		rc = EIO;
		goto out;
	}

	add_verify_status(&st, VE_VERIFIED);

	md->init(&ctx.vtable);
	md->update(&ctx.vtable, content, st.st_size);
	md->out(&ctx.vtable, digest);

	if (prefix == NULL)
		manifest_prefix[0] = '\0';
	else
		strcpy(manifest_prefix, prefix);

	strcpy(manifest_path, path);

	hexdigest(manifest_hash, 2 * br_sha256_SIZE + 2,
	    digest, br_sha256_SIZE);
	manifest_hash[2*br_sha256_SIZE] = '\0';

	manifest_present = 1;
	rc = 0;

out:
	if (content != NULL)
		free(content);

	return (rc);
}