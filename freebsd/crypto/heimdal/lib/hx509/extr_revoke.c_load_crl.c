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
typedef  int /*<<< orphan*/  time_t ;
struct stat {int /*<<< orphan*/  st_mtime; } ;
struct TYPE_7__ {int length; } ;
struct TYPE_8__ {TYPE_1__ signatureValue; } ;
typedef  TYPE_2__ CRLCertificateList ;

/* Variables and functions */
 int HX509_CRYPTO_SIG_INVALID_FORMAT ; 
 int decode_CRLCertificateList (void*,size_t,TYPE_2__*,size_t*) ; 
 int errno ; 
 int /*<<< orphan*/  free_CRLCertificateList (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int rk_undumpdata (char const*,void**,size_t*) ; 
 int /*<<< orphan*/  rk_xfree (void*) ; 
 int stat (char const*,struct stat*) ; 

__attribute__((used)) static int
load_crl(const char *path, time_t *t, CRLCertificateList *crl)
{
    size_t length, size;
    struct stat sb;
    void *data;
    int ret;

    memset(crl, 0, sizeof(*crl));

    ret = rk_undumpdata(path, &data, &length);
    if (ret)
	return ret;

    ret = stat(path, &sb);
    if (ret)
	return errno;

    *t = sb.st_mtime;

    ret = decode_CRLCertificateList(data, length, crl, &size);
    rk_xfree(data);
    if (ret)
	return ret;

    /* check signature is aligned */
    if (crl->signatureValue.length & 7) {
	free_CRLCertificateList(crl);
	return HX509_CRYPTO_SIG_INVALID_FORMAT;
    }
    return 0;
}