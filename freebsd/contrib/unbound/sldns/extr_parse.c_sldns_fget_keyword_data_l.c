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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ LDNS_MAX_KEYWORDLEN ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int sldns_fget_token (int /*<<< orphan*/ *,char*,char const*,scalar_t__) ; 
 int sldns_fget_token_l (int /*<<< orphan*/ *,char*,char const*,size_t,int*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,scalar_t__) ; 

ssize_t
sldns_fget_keyword_data_l(FILE *f, const char *keyword, const char *k_del, char *data,
               const char *d_del, size_t data_limit, int *line_nr)
{
       /* we assume: keyword|sep|data */
       char *fkeyword;
       ssize_t i;

       if(strlen(keyword) >= LDNS_MAX_KEYWORDLEN)
               return -1;
       fkeyword = (char*)malloc(LDNS_MAX_KEYWORDLEN);
       if(!fkeyword)
               return -1;

       i = sldns_fget_token(f, fkeyword, k_del, LDNS_MAX_KEYWORDLEN);
       if(i==0 || i==-1) {
               free(fkeyword);
               return -1;
       }

       /* case??? i instead of strlen? */
       if (strncmp(fkeyword, keyword, LDNS_MAX_KEYWORDLEN - 1) == 0) {
               /* whee! */
               /* printf("%s\n%s\n", "Matching keyword", fkeyword); */
               i = sldns_fget_token_l(f, data, d_del, data_limit, line_nr);
               free(fkeyword);
               return i;
       } else {
               /*printf("no match for %s (read: %s)\n", keyword, fkeyword);*/
               free(fkeyword);
               return -1;
       }
}