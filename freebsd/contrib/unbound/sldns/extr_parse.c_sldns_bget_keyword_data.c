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
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ LDNS_MAX_KEYWORDLEN ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int sldns_bget_token (int /*<<< orphan*/ *,char*,char const*,size_t) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,scalar_t__) ; 

ssize_t
sldns_bget_keyword_data(sldns_buffer *b, const char *keyword, const char *k_del, char
*data, const char *d_del, size_t data_limit)
{
       /* we assume: keyword|sep|data */
       char *fkeyword;
       ssize_t i;

       if(strlen(keyword) >= LDNS_MAX_KEYWORDLEN)
               return -1;
       fkeyword = (char*)malloc(LDNS_MAX_KEYWORDLEN);
       if(!fkeyword)
               return -1; /* out of memory */

       i = sldns_bget_token(b, fkeyword, k_del, data_limit);
       if(i==0 || i==-1) {
               free(fkeyword);
               return -1; /* nothing read */
       }

       /* case??? */
       if (strncmp(fkeyword, keyword, strlen(keyword)) == 0) {
               free(fkeyword);
               /* whee, the match! */
               /* retrieve it's data */
               i = sldns_bget_token(b, data, d_del, 0);
               return i;
       } else {
               free(fkeyword);
               return -1;
       }
}