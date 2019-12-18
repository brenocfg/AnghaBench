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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct compareInfo {int matchOne; int matchAll; scalar_t__ noCase; scalar_t__ matchSet; } ;

/* Variables and functions */
 int SQLITE_MATCH ; 
 int SQLITE_NOMATCH ; 
 int SQLITE_NOWILDCARDMATCH ; 
 int /*<<< orphan*/  SQLITE_SKIP_UTF8 (scalar_t__ const*) ; 
 int Utf8Read (scalar_t__ const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 char sqlite3Tolower (int) ; 
 char sqlite3Toupper (int) ; 
 int sqlite3Utf8Read (scalar_t__ const**) ; 
 int /*<<< orphan*/  strcspn (char const*,char*) ; 

__attribute__((used)) static int patternCompare(
  const u8 *zPattern,              /* The glob pattern */
  const u8 *zString,               /* The string to compare against the glob */
  const struct compareInfo *pInfo, /* Information about how to do the compare */
  u32 matchOther                   /* The escape char (LIKE) or '[' (GLOB) */
){
  u32 c, c2;                       /* Next pattern and input string chars */
  u32 matchOne = pInfo->matchOne;  /* "?" or "_" */
  u32 matchAll = pInfo->matchAll;  /* "*" or "%" */
  u8 noCase = pInfo->noCase;       /* True if uppercase==lowercase */
  const u8 *zEscaped = 0;          /* One past the last escaped input char */
  
  while( (c = Utf8Read(zPattern))!=0 ){
    if( c==matchAll ){  /* Match "*" */
      /* Skip over multiple "*" characters in the pattern.  If there
      ** are also "?" characters, skip those as well, but consume a
      ** single character of the input string for each "?" skipped */
      while( (c=Utf8Read(zPattern)) == matchAll || c == matchOne ){
        if( c==matchOne && sqlite3Utf8Read(&zString)==0 ){
          return SQLITE_NOWILDCARDMATCH;
        }
      }
      if( c==0 ){
        return SQLITE_MATCH;   /* "*" at the end of the pattern matches */
      }else if( c==matchOther ){
        if( pInfo->matchSet==0 ){
          c = sqlite3Utf8Read(&zPattern);
          if( c==0 ) return SQLITE_NOWILDCARDMATCH;
        }else{
          /* "[...]" immediately follows the "*".  We have to do a slow
          ** recursive search in this case, but it is an unusual case. */
          assert( matchOther<0x80 );  /* '[' is a single-byte character */
          while( *zString ){
            int bMatch = patternCompare(&zPattern[-1],zString,pInfo,matchOther);
            if( bMatch!=SQLITE_NOMATCH ) return bMatch;
            SQLITE_SKIP_UTF8(zString);
          }
          return SQLITE_NOWILDCARDMATCH;
        }
      }

      /* At this point variable c contains the first character of the
      ** pattern string past the "*".  Search in the input string for the
      ** first matching character and recursively continue the match from
      ** that point.
      **
      ** For a case-insensitive search, set variable cx to be the same as
      ** c but in the other case and search the input string for either
      ** c or cx.
      */
      if( c<=0x80 ){
        char zStop[3];
        int bMatch;
        if( noCase ){
          zStop[0] = sqlite3Toupper(c);
          zStop[1] = sqlite3Tolower(c);
          zStop[2] = 0;
        }else{
          zStop[0] = c;
          zStop[1] = 0;
        }
        while(1){
          zString += strcspn((const char*)zString, zStop);
          if( zString[0]==0 ) break;
          zString++;
          bMatch = patternCompare(zPattern,zString,pInfo,matchOther);
          if( bMatch!=SQLITE_NOMATCH ) return bMatch;
        }
      }else{
        int bMatch;
        while( (c2 = Utf8Read(zString))!=0 ){
          if( c2!=c ) continue;
          bMatch = patternCompare(zPattern,zString,pInfo,matchOther);
          if( bMatch!=SQLITE_NOMATCH ) return bMatch;
        }
      }
      return SQLITE_NOWILDCARDMATCH;
    }
    if( c==matchOther ){
      if( pInfo->matchSet==0 ){
        c = sqlite3Utf8Read(&zPattern);
        if( c==0 ) return SQLITE_NOMATCH;
        zEscaped = zPattern;
      }else{
        u32 prior_c = 0;
        int seen = 0;
        int invert = 0;
        c = sqlite3Utf8Read(&zString);
        if( c==0 ) return SQLITE_NOMATCH;
        c2 = sqlite3Utf8Read(&zPattern);
        if( c2=='^' ){
          invert = 1;
          c2 = sqlite3Utf8Read(&zPattern);
        }
        if( c2==']' ){
          if( c==']' ) seen = 1;
          c2 = sqlite3Utf8Read(&zPattern);
        }
        while( c2 && c2!=']' ){
          if( c2=='-' && zPattern[0]!=']' && zPattern[0]!=0 && prior_c>0 ){
            c2 = sqlite3Utf8Read(&zPattern);
            if( c>=prior_c && c<=c2 ) seen = 1;
            prior_c = 0;
          }else{
            if( c==c2 ){
              seen = 1;
            }
            prior_c = c2;
          }
          c2 = sqlite3Utf8Read(&zPattern);
        }
        if( c2==0 || (seen ^ invert)==0 ){
          return SQLITE_NOMATCH;
        }
        continue;
      }
    }
    c2 = Utf8Read(zString);
    if( c==c2 ) continue;
    if( noCase  && sqlite3Tolower(c)==sqlite3Tolower(c2) && c<0x80 && c2<0x80 ){
      continue;
    }
    if( c==matchOne && zPattern!=zEscaped && c2!=0 ) continue;
    return SQLITE_NOMATCH;
  }
  return *zString==0 ? SQLITE_MATCH : SQLITE_NOMATCH;
}