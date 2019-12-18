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
typedef  int /*<<< orphan*/  TS_TST_INFO ;
typedef  int /*<<< orphan*/  TS_STATUS_INFO ;
typedef  int /*<<< orphan*/  TS_RESP ;
typedef  int /*<<< orphan*/  PKCS7 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  PKCS7_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PKCS7_to_TS_TST_INFO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_RESP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TS_RESP_new () ; 
 int /*<<< orphan*/  TS_RESP_set_status_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_RESP_set_tst_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_STATUS_GRANTED ; 
 int /*<<< orphan*/  TS_STATUS_INFO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TS_STATUS_INFO_new () ; 
 int /*<<< orphan*/  TS_STATUS_INFO_set_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_TST_INFO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_PKCS7_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static TS_RESP *read_PKCS7(BIO *in_bio)
{
    int ret = 0;
    PKCS7 *token = NULL;
    TS_TST_INFO *tst_info = NULL;
    TS_RESP *resp = NULL;
    TS_STATUS_INFO *si = NULL;

    if ((token = d2i_PKCS7_bio(in_bio, NULL)) == NULL)
        goto end;
    if ((tst_info = PKCS7_to_TS_TST_INFO(token)) == NULL)
        goto end;
    if ((resp = TS_RESP_new()) == NULL)
        goto end;
    if ((si = TS_STATUS_INFO_new()) == NULL)
        goto end;
    if (!TS_STATUS_INFO_set_status(si, TS_STATUS_GRANTED))
        goto end;
    if (!TS_RESP_set_status_info(resp, si))
        goto end;
    TS_RESP_set_tst_info(resp, token, tst_info);
    token = NULL;               /* Ownership is lost. */
    tst_info = NULL;            /* Ownership is lost. */
    ret = 1;

 end:
    PKCS7_free(token);
    TS_TST_INFO_free(tst_info);
    if (!ret) {
        TS_RESP_free(resp);
        resp = NULL;
    }
    TS_STATUS_INFO_free(si);
    return resp;
}