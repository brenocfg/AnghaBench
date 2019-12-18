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
typedef  int /*<<< orphan*/  u_int32 ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int /*<<< orphan*/  addr_refid ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_NON_FIPS_ALLOW ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int /*<<< orphan*/  INIT_SSL () ; 
 scalar_t__ IS_IPV4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NSRCADR (int /*<<< orphan*/ *) ; 
 scalar_t__ PSOCK_ADDR6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 

u_int32
addr2refid(sockaddr_u *addr)
{
	u_char		digest[EVP_MAX_MD_SIZE];
	u_int32		addr_refid;
	EVP_MD_CTX	*ctx;
	u_int		len;

	if (IS_IPV4(addr))
		return (NSRCADR(addr));

	INIT_SSL();

	ctx = EVP_MD_CTX_new();
#   ifdef EVP_MD_CTX_FLAG_NON_FIPS_ALLOW
	/* MD5 is not used as a crypto hash here. */
	EVP_MD_CTX_set_flags(ctx, EVP_MD_CTX_FLAG_NON_FIPS_ALLOW);
#   endif
	/* [Bug 3457] DON'T use plain EVP_DigestInit! It would kill the
	 * flags! */
	if (!EVP_DigestInit_ex(ctx, EVP_md5(), NULL)) {
		msyslog(LOG_ERR,
		    "MD5 init failed");
		EVP_MD_CTX_free(ctx);	/* pedantic... but safe */
		exit(1);
	}

	EVP_DigestUpdate(ctx, (u_char *)PSOCK_ADDR6(addr),
	    sizeof(struct in6_addr));
	EVP_DigestFinal(ctx, digest, &len);
	EVP_MD_CTX_free(ctx);
	memcpy(&addr_refid, digest, sizeof(addr_refid));
	return (addr_refid);
}