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
          "$argon2i$v=19$m=4096,t=1,p=1$X1NhbHQAAAAAAAAAAAAAAA$bWh++"
          "MKN1OiFHKgIWTLvIi1iHicmHH7+Fv3K88ifFfI" },
        { "",
          "$argon2i$v=19$m=2048,t=4,p=1$SWkxaUhpY21ISDcrRnYzSw$Mbg/"
          "Eck1kpZir5T9io7C64cpffdTBaORgyriLQFgQj8" },
        { "^T5H$JYt39n%K*j:W]!1s?vg!:jGi]Ax?..l7[p0v:1jHTpla9;]bUN;?bWyCbtqg ",
          "$argon2i$v=19$m=4096,t=3,p=2$X1NhbHQAAAAAAAAAAAAAAA$z/QMiU4lQxGsYNc/"
          "+K/bizwsA1P11UG2dj/7+aILJ4I" },
        { "K3S=KyH#)36_?]LxeR8QNKw6X=gFbxai$C%29V*",
          "$argon2i$v=19$m=4096,t=3,p=1$X1NhbHQAAAAAAAAAAAAAAA$fu2Wsecyt+"
          "yPnBvSvYN16oP5ozRmkp0ixJ1YL19V3Uo" }
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
            printf("[tv3] pwhash_str failure (maybe intentional): [%u]\n",
                   (unsigned int) i);
        }
    } while (++i < (sizeof tests) / (sizeof tests[0]));
}