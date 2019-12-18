#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp_buf ;
typedef  int /*<<< orphan*/  ebcdic_buf ;
struct TYPE_12__ {TYPE_1__* value; int /*<<< orphan*/  object; } ;
typedef  TYPE_2__ X509_NAME_ENTRY ;
struct TYPE_13__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_3__ X509_NAME ;
struct TYPE_14__ {char* data; } ;
struct TYPE_11__ {int type; int length; unsigned char* data; } ;
typedef  TYPE_4__ BUF_MEM ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_MEM_free (TYPE_4__*) ; 
 int /*<<< orphan*/  BUF_MEM_grow (TYPE_4__*,int) ; 
 TYPE_4__* BUF_MEM_new () ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int NAME_ONELINE_MAX ; 
 int NID_undef ; 
 char* OBJ_nid2sn (int) ; 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_4__*) ; 
 int V_ASN1_GENERALSTRING ; 
 int V_ASN1_IA5STRING ; 
 int V_ASN1_PRINTABLESTRING ; 
 int V_ASN1_TELETEXSTRING ; 
 int V_ASN1_VISIBLESTRING ; 
 int /*<<< orphan*/  X509_F_X509_NAME_ONELINE ; 
 int /*<<< orphan*/  X509_R_NAME_TOO_LONG ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ascii2ebcdic (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  i2t_ASN1_OBJECT (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 int* os_toascii ; 
 int sk_X509_NAME_ENTRY_num (int /*<<< orphan*/ ) ; 
 TYPE_2__* sk_X509_NAME_ENTRY_value (int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

char *X509_NAME_oneline(const X509_NAME *a, char *buf, int len)
{
    const X509_NAME_ENTRY *ne;
    int i;
    int n, lold, l, l1, l2, num, j, type;
    const char *s;
    char *p;
    unsigned char *q;
    BUF_MEM *b = NULL;
    static const char hex[17] = "0123456789ABCDEF";
    int gs_doit[4];
    char tmp_buf[80];
#ifdef CHARSET_EBCDIC
    unsigned char ebcdic_buf[1024];
#endif

    if (buf == NULL) {
        if ((b = BUF_MEM_new()) == NULL)
            goto err;
        if (!BUF_MEM_grow(b, 200))
            goto err;
        b->data[0] = '\0';
        len = 200;
    } else if (len == 0) {
        return NULL;
    }
    if (a == NULL) {
        if (b) {
            buf = b->data;
            OPENSSL_free(b);
        }
        strncpy(buf, "NO X509_NAME", len);
        buf[len - 1] = '\0';
        return buf;
    }

    len--;                      /* space for '\0' */
    l = 0;
    for (i = 0; i < sk_X509_NAME_ENTRY_num(a->entries); i++) {
        ne = sk_X509_NAME_ENTRY_value(a->entries, i);
        n = OBJ_obj2nid(ne->object);
        if ((n == NID_undef) || ((s = OBJ_nid2sn(n)) == NULL)) {
            i2t_ASN1_OBJECT(tmp_buf, sizeof(tmp_buf), ne->object);
            s = tmp_buf;
        }
        l1 = strlen(s);

        type = ne->value->type;
        num = ne->value->length;
        if (num > NAME_ONELINE_MAX) {
            X509err(X509_F_X509_NAME_ONELINE, X509_R_NAME_TOO_LONG);
            goto end;
        }
        q = ne->value->data;
#ifdef CHARSET_EBCDIC
        if (type == V_ASN1_GENERALSTRING ||
            type == V_ASN1_VISIBLESTRING ||
            type == V_ASN1_PRINTABLESTRING ||
            type == V_ASN1_TELETEXSTRING ||
            type == V_ASN1_IA5STRING) {
            if (num > (int)sizeof(ebcdic_buf))
                num = sizeof(ebcdic_buf);
            ascii2ebcdic(ebcdic_buf, q, num);
            q = ebcdic_buf;
        }
#endif

        if ((type == V_ASN1_GENERALSTRING) && ((num % 4) == 0)) {
            gs_doit[0] = gs_doit[1] = gs_doit[2] = gs_doit[3] = 0;
            for (j = 0; j < num; j++)
                if (q[j] != 0)
                    gs_doit[j & 3] = 1;

            if (gs_doit[0] | gs_doit[1] | gs_doit[2])
                gs_doit[0] = gs_doit[1] = gs_doit[2] = gs_doit[3] = 1;
            else {
                gs_doit[0] = gs_doit[1] = gs_doit[2] = 0;
                gs_doit[3] = 1;
            }
        } else
            gs_doit[0] = gs_doit[1] = gs_doit[2] = gs_doit[3] = 1;

        for (l2 = j = 0; j < num; j++) {
            if (!gs_doit[j & 3])
                continue;
            l2++;
#ifndef CHARSET_EBCDIC
            if ((q[j] < ' ') || (q[j] > '~'))
                l2 += 3;
#else
            if ((os_toascii[q[j]] < os_toascii[' ']) ||
                (os_toascii[q[j]] > os_toascii['~']))
                l2 += 3;
#endif
        }

        lold = l;
        l += 1 + l1 + 1 + l2;
        if (l > NAME_ONELINE_MAX) {
            X509err(X509_F_X509_NAME_ONELINE, X509_R_NAME_TOO_LONG);
            goto end;
        }
        if (b != NULL) {
            if (!BUF_MEM_grow(b, l + 1))
                goto err;
            p = &(b->data[lold]);
        } else if (l > len) {
            break;
        } else
            p = &(buf[lold]);
        *(p++) = '/';
        memcpy(p, s, (unsigned int)l1);
        p += l1;
        *(p++) = '=';

#ifndef CHARSET_EBCDIC          /* q was assigned above already. */
        q = ne->value->data;
#endif

        for (j = 0; j < num; j++) {
            if (!gs_doit[j & 3])
                continue;
#ifndef CHARSET_EBCDIC
            n = q[j];
            if ((n < ' ') || (n > '~')) {
                *(p++) = '\\';
                *(p++) = 'x';
                *(p++) = hex[(n >> 4) & 0x0f];
                *(p++) = hex[n & 0x0f];
            } else
                *(p++) = n;
#else
            n = os_toascii[q[j]];
            if ((n < os_toascii[' ']) || (n > os_toascii['~'])) {
                *(p++) = '\\';
                *(p++) = 'x';
                *(p++) = hex[(n >> 4) & 0x0f];
                *(p++) = hex[n & 0x0f];
            } else
                *(p++) = q[j];
#endif
        }
        *p = '\0';
    }
    if (b != NULL) {
        p = b->data;
        OPENSSL_free(b);
    } else
        p = buf;
    if (i == 0)
        *p = '\0';
    return p;
 err:
    X509err(X509_F_X509_NAME_ONELINE, ERR_R_MALLOC_FAILURE);
 end:
    BUF_MEM_free(b);
    return NULL;
}