#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_SIG ;
typedef  int /*<<< orphan*/  X509_ALGOR ;
typedef  int /*<<< orphan*/  UI_METHOD ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {char* data; size_t max; size_t length; } ;
typedef  int /*<<< orphan*/  OSSL_STORE_INFO ;
typedef  TYPE_1__ BUF_MEM ;
typedef  TYPE_2__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_MEM_free (TYPE_1__*) ; 
 TYPE_1__* BUF_MEM_new () ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OSSL_STORE_F_TRY_DECODE_PKCS8ENCRYPTED ; 
 int /*<<< orphan*/  OSSL_STORE_R_BAD_PASSWORD_READ ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PEM_BUFSIZE ; 
 int /*<<< orphan*/  PEM_STRING_PKCS8 ; 
 int /*<<< orphan*/  PEM_STRING_PKCS8INF ; 
 int /*<<< orphan*/  PKCS12_pbe_crypt (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char**,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_SIG_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_SIG_get0 (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,TYPE_2__ const**) ; 
 int /*<<< orphan*/ * d2i_X509_SIG (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 char* file_get_pass (int /*<<< orphan*/  const*,char*,int,char*,void*) ; 
 int /*<<< orphan*/ * ossl_store_info_new_EMBEDDED (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static OSSL_STORE_INFO *try_decode_PKCS8Encrypted(const char *pem_name,
                                                  const char *pem_header,
                                                  const unsigned char *blob,
                                                  size_t len, void **pctx,
                                                  int *matchcount,
                                                  const UI_METHOD *ui_method,
                                                  void *ui_data)
{
    X509_SIG *p8 = NULL;
    char kbuf[PEM_BUFSIZE];
    char *pass = NULL;
    const X509_ALGOR *dalg = NULL;
    const ASN1_OCTET_STRING *doct = NULL;
    OSSL_STORE_INFO *store_info = NULL;
    BUF_MEM *mem = NULL;
    unsigned char *new_data = NULL;
    int new_data_len;

    if (pem_name != NULL) {
        if (strcmp(pem_name, PEM_STRING_PKCS8) != 0)
            return NULL;
        *matchcount = 1;
    }

    if ((p8 = d2i_X509_SIG(NULL, &blob, len)) == NULL)
        return NULL;

    *matchcount = 1;

    if ((mem = BUF_MEM_new()) == NULL) {
        OSSL_STOREerr(OSSL_STORE_F_TRY_DECODE_PKCS8ENCRYPTED,
                      ERR_R_MALLOC_FAILURE);
        goto nop8;
    }

    if ((pass = file_get_pass(ui_method, kbuf, PEM_BUFSIZE,
                              "PKCS8 decrypt password", ui_data)) == NULL) {
        OSSL_STOREerr(OSSL_STORE_F_TRY_DECODE_PKCS8ENCRYPTED,
                      OSSL_STORE_R_BAD_PASSWORD_READ);
        goto nop8;
    }

    X509_SIG_get0(p8, &dalg, &doct);
    if (!PKCS12_pbe_crypt(dalg, pass, strlen(pass), doct->data, doct->length,
                          &new_data, &new_data_len, 0))
        goto nop8;

    mem->data = (char *)new_data;
    mem->max = mem->length = (size_t)new_data_len;
    X509_SIG_free(p8);

    store_info = ossl_store_info_new_EMBEDDED(PEM_STRING_PKCS8INF, mem);
    if (store_info == NULL) {
        OSSL_STOREerr(OSSL_STORE_F_TRY_DECODE_PKCS8ENCRYPTED,
                      ERR_R_MALLOC_FAILURE);
        goto nop8;
    }

    return store_info;
 nop8:
    X509_SIG_free(p8);
    BUF_MEM_free(mem);
    return NULL;
}