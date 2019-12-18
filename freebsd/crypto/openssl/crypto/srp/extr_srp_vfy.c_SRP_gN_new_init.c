#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_6__ {struct TYPE_6__* b64_bn; int /*<<< orphan*/  bn; } ;
typedef  TYPE_1__ SRP_gN_cache ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int MAX_LEN ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 TYPE_1__* OPENSSL_strdup (char const*) ; 
 int t_fromb64 (unsigned char*,int,char const*) ; 

__attribute__((used)) static SRP_gN_cache *SRP_gN_new_init(const char *ch)
{
    unsigned char tmp[MAX_LEN];
    int len;
    SRP_gN_cache *newgN = OPENSSL_malloc(sizeof(*newgN));

    if (newgN == NULL)
        return NULL;

    len = t_fromb64(tmp, sizeof(tmp), ch);
    if (len < 0)
        goto err;

    if ((newgN->b64_bn = OPENSSL_strdup(ch)) == NULL)
        goto err;

    if ((newgN->bn = BN_bin2bn(tmp, len, NULL)))
        return newgN;

    OPENSSL_free(newgN->b64_bn);
 err:
    OPENSSL_free(newgN);
    return NULL;
}