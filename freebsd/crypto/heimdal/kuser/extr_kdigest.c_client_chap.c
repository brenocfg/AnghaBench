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
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int MD5_DIGEST_LENGTH ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hex_encode (unsigned char*,int,char**) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
client_chap(const void *server_nonce, size_t snoncelen,
	    unsigned char server_identifier,
	    const char *password)
{
    EVP_MD_CTX *ctx;
    unsigned char md[MD5_DIGEST_LENGTH];
    char *h;

    ctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(ctx, EVP_md5(), NULL);

    EVP_DigestUpdate(ctx, &server_identifier, 1);
    EVP_DigestUpdate(ctx, password, strlen(password));
    EVP_DigestUpdate(ctx, server_nonce, snoncelen);
    EVP_DigestFinal_ex(ctx, md, NULL);

    EVP_MD_CTX_destroy(ctx);

    hex_encode(md, 16, &h);

    printf("responseData=%s\n", h);
    free(h);
}