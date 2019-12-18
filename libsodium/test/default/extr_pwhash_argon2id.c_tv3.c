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

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int crypto_pwhash_str_verify (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 int /*<<< orphan*/  sodium_free (char*) ; 
 scalar_t__ sodium_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
tv3(void)
{
    static struct {
        const char *passwd;
        const char *out;
    } tests[] = {
        { "",
          "$argon2id$v=19$m=4096,t=0,p=1$X1NhbHQAAAAAAAAAAAAAAA$bWh++MKN1OiFHKgIWTLvIi1iHicmHH7+Fv3K88ifFfI" },
        { "",
          "$argon2id$v=19$m=2048,t=4,p=1$SWkxaUhpY21ISDcrRnYzSw$Mbg/Eck1kpZir5T9io7C64cpffdTBaORgyriLQFgQj8" },
        { "",
          "$argon2id$v=19$m=4882,t=2,p=1$bA81arsiXysd3WbTRzmEOw$Nm8QBM+7RH1DXo9rvp5cwKEOOOfD2g6JuxlXihoNcpE" },
        { "^T5H$JYt39n%K*j:W]!1s?vg!:jGi]Ax?..l7[p0v:1jHTpla9;]bUN;?bWyCbtqg ",
          "$argon2id$v=19$m=4096,t=0,p=1$PkEgMTYtYnl0ZXMgc2FsdA$ltB/ue1kPtBMBGfsysMpPigE6hiNEKZ9vs8vLNVDQGA" },
        { "^T5H$JYt39n%K*j:W]!1s?vg!:jGi]Ax?..l7[p0v:1jHTpla9;]bUN;?bWyCbtqg ",
          "$argon2id$v=19$m=4096,t=19,p=1$PkEgMTYtYnl0ZXMgc2FsdA$ltB/ue1kPtBMBGfsysMpPigE6hiNEKZ9vs8vLNVDQGA" },
        { "K3S=KyH#)36_?]LxeR8QNKw6X=gFbxai$C%29V*",
          "$argon2id$v=19$m=4096,t=1,p=3$PkEgcHJldHR5IGxvbmcgc2FsdA$HUqx5Z1b/ZypnUrvvJ5UC2Q+T6Q1WwASK/Kr9dRbGA0" }
    };
    char   *out;
    char   *passwd;
    size_t  i = 0U;
    int     ret;

    do {
        out = (char *) sodium_malloc(strlen(tests[i].out) + 1U);
        assert(out != NULL);
        memcpy(out, tests[i].out, strlen(tests[i].out) + 1U);
        passwd = (char *) sodium_malloc(strlen(tests[i].passwd) + 1U);
        assert(passwd != NULL);
        memcpy(passwd, tests[i].passwd, strlen(tests[i].passwd) + 1U);
        ret = crypto_pwhash_str_verify(out, passwd, strlen(passwd));
        sodium_free(out);
        sodium_free(passwd);
        if (ret != 0) {
            printf("[tv3] pwhash_argon2id_str failure (maybe intentional): [%u]\n",
                   (unsigned int) i);
        }
    } while (++i < (sizeof tests) / (sizeof tests[0]));
}