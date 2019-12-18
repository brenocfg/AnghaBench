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
typedef  unsigned int apr_uint32_t ;
typedef  int apr_ssize_t ;

/* Variables and functions */
 int APR_HASH_KEY_STRING ; 
 int strlen (char const*) ; 

__attribute__((used)) static unsigned int
hashfunc_compatible(const char *char_key, apr_ssize_t *klen)
{
    unsigned int hash = 0;
    const unsigned char *key = (const unsigned char *)char_key;
    const unsigned char *p;
    apr_ssize_t i;

    if (*klen == APR_HASH_KEY_STRING)
      *klen = strlen(char_key);

#if SVN_UNALIGNED_ACCESS_IS_OK
    for (p = key, i = *klen; i >= 4; i-=4, p+=4)
      {
        apr_uint32_t chunk = *(const apr_uint32_t *)p;

        /* the ">> 17" part gives upper bits in the chunk a chance to make
           some impact as well */
        hash = hash * 33 * 33 * 33 * 33 + chunk + (chunk >> 17);
      }
#else
    for (p = key, i = *klen; i >= 4; i-=4, p+=4)
      {
        hash = hash * 33 * 33 * 33 * 33
              + p[0] * 33 * 33 * 33
              + p[1] * 33 * 33
              + p[2] * 33
              + p[3];
      }
#endif
    for (; i; i--, p++)
        hash = hash * 33 + *p;

    return hash;
}