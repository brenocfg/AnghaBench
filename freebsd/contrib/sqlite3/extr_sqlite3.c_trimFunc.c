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
typedef  unsigned char u8 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int i64 ;

/* Variables and functions */
 scalar_t__ SQLITE_NULL ; 
 int SQLITE_PTR_TO_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQLITE_SKIP_UTF8 (unsigned char const*) ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned char** contextMalloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ memcmp (unsigned char const*,unsigned char*,int) ; 
 int /*<<< orphan*/  sqlite3_free (unsigned char**) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_user_data (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 unsigned char const* sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void trimFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  const unsigned char *zIn;         /* Input string */
  const unsigned char *zCharSet;    /* Set of characters to trim */
  int nIn;                          /* Number of bytes in input */
  int flags;                        /* 1: trimleft  2: trimright  3: trim */
  int i;                            /* Loop counter */
  unsigned char *aLen = 0;          /* Length of each character in zCharSet */
  unsigned char **azChar = 0;       /* Individual characters in zCharSet */
  int nChar;                        /* Number of characters in zCharSet */

  if( sqlite3_value_type(argv[0])==SQLITE_NULL ){
    return;
  }
  zIn = sqlite3_value_text(argv[0]);
  if( zIn==0 ) return;
  nIn = sqlite3_value_bytes(argv[0]);
  assert( zIn==sqlite3_value_text(argv[0]) );
  if( argc==1 ){
    static const unsigned char lenOne[] = { 1 };
    static unsigned char * const azOne[] = { (u8*)" " };
    nChar = 1;
    aLen = (u8*)lenOne;
    azChar = (unsigned char **)azOne;
    zCharSet = 0;
  }else if( (zCharSet = sqlite3_value_text(argv[1]))==0 ){
    return;
  }else{
    const unsigned char *z;
    for(z=zCharSet, nChar=0; *z; nChar++){
      SQLITE_SKIP_UTF8(z);
    }
    if( nChar>0 ){
      azChar = contextMalloc(context, ((i64)nChar)*(sizeof(char*)+1));
      if( azChar==0 ){
        return;
      }
      aLen = (unsigned char*)&azChar[nChar];
      for(z=zCharSet, nChar=0; *z; nChar++){
        azChar[nChar] = (unsigned char *)z;
        SQLITE_SKIP_UTF8(z);
        aLen[nChar] = (u8)(z - azChar[nChar]);
      }
    }
  }
  if( nChar>0 ){
    flags = SQLITE_PTR_TO_INT(sqlite3_user_data(context));
    if( flags & 1 ){
      while( nIn>0 ){
        int len = 0;
        for(i=0; i<nChar; i++){
          len = aLen[i];
          if( len<=nIn && memcmp(zIn, azChar[i], len)==0 ) break;
        }
        if( i>=nChar ) break;
        zIn += len;
        nIn -= len;
      }
    }
    if( flags & 2 ){
      while( nIn>0 ){
        int len = 0;
        for(i=0; i<nChar; i++){
          len = aLen[i];
          if( len<=nIn && memcmp(&zIn[nIn-len],azChar[i],len)==0 ) break;
        }
        if( i>=nChar ) break;
        nIn -= len;
      }
    }
    if( zCharSet ){
      sqlite3_free(azChar);
    }
  }
  sqlite3_result_text(context, (char*)zIn, nIn, SQLITE_TRANSIENT);
}