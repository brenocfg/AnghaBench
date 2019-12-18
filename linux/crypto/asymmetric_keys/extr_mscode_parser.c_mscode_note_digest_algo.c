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
struct pefile_context {char* digest_algo; } ;
typedef  enum OID { ____Placeholder_OID } OID ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int EBADMSG ; 
 int ENOPKG ; 
#define  OID__NR 135 
#define  OID_md4 134 
#define  OID_md5 133 
#define  OID_sha1 132 
#define  OID_sha224 131 
#define  OID_sha256 130 
#define  OID_sha384 129 
#define  OID_sha512 128 
 int look_up_OID (void const*,size_t) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  sprint_oid (void const*,size_t,char*,int) ; 

int mscode_note_digest_algo(void *context, size_t hdrlen,
			    unsigned char tag,
			    const void *value, size_t vlen)
{
	struct pefile_context *ctx = context;
	char buffer[50];
	enum OID oid;

	oid = look_up_OID(value, vlen);
	switch (oid) {
	case OID_md4:
		ctx->digest_algo = "md4";
		break;
	case OID_md5:
		ctx->digest_algo = "md5";
		break;
	case OID_sha1:
		ctx->digest_algo = "sha1";
		break;
	case OID_sha256:
		ctx->digest_algo = "sha256";
		break;
	case OID_sha384:
		ctx->digest_algo = "sha384";
		break;
	case OID_sha512:
		ctx->digest_algo = "sha512";
		break;
	case OID_sha224:
		ctx->digest_algo = "sha224";
		break;

	case OID__NR:
		sprint_oid(value, vlen, buffer, sizeof(buffer));
		pr_err("Unknown OID: %s\n", buffer);
		return -EBADMSG;

	default:
		pr_err("Unsupported content type: %u\n", oid);
		return -ENOPKG;
	}

	return 0;
}