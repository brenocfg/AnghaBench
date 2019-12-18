#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_9__ {int /*<<< orphan*/  vtable; } ;
typedef  TYPE_1__ br_hash_compat_context ;
struct TYPE_10__ {int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,unsigned char*,int) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ br_hash_class ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int VE_FINGERPRINT_IGNORE ; 
 int VE_FINGERPRINT_UNKNOWN ; 
 size_t br_sha1_SIZE ; 
 TYPE_2__ br_sha1_vtable ; 
 size_t br_sha256_SIZE ; 
 TYPE_2__ br_sha256_vtable ; 
 size_t br_sha384_SIZE ; 
 TYPE_2__ br_sha384_vtable ; 
 size_t br_sha512_SIZE ; 
 TYPE_2__ br_sha512_vtable ; 
 int /*<<< orphan*/  lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int read (int,unsigned char*,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int ve_check_hash (TYPE_1__*,TYPE_2__ const*,char const*,char const*,size_t) ; 
 int /*<<< orphan*/  ve_error_set (char*,char const*) ; 

__attribute__((used)) static int
verify_fingerprint(int fd, const char *path, const char *cp, off_t off)
{
	unsigned char buf[PAGE_SIZE];
	const br_hash_class *md;
	br_hash_compat_context mctx;
	size_t hlen;
	int n;

	if (strncmp(cp, "no_hash", 7) == 0) {
		return (VE_FINGERPRINT_IGNORE);
	} else if (strncmp(cp, "sha256=", 7) == 0) {
		md = &br_sha256_vtable;
		hlen = br_sha256_SIZE;
		cp += 7;
#ifdef VE_SHA1_SUPPORT
	} else if (strncmp(cp, "sha1=", 5) == 0) {
		md = &br_sha1_vtable;
		hlen = br_sha1_SIZE;
		cp += 5;
#endif
#ifdef VE_SHA384_SUPPORT
	} else if (strncmp(cp, "sha384=", 7) == 0) {
		md = &br_sha384_vtable;
		hlen = br_sha384_SIZE;
		cp += 7;
#endif
#ifdef VE_SHA512_SUPPORT
	} else if (strncmp(cp, "sha512=", 7) == 0) {
		md = &br_sha512_vtable;
		hlen = br_sha512_SIZE;
		cp += 7;
#endif
	} else {
		ve_error_set("%s: no supported fingerprint", path);
		return (VE_FINGERPRINT_UNKNOWN);
	}

	md->init(&mctx.vtable);
	if (off)
		lseek(fd, 0, SEEK_SET);
	do {
		n = read(fd, buf, sizeof(buf));
		if (n < 0)
			return (n);
		if (n > 0)
			md->update(&mctx.vtable, buf, n);
	} while (n > 0);
	lseek(fd, off, SEEK_SET);
	return (ve_check_hash(&mctx, md, path, cp, hlen));
}