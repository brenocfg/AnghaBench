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
 int* aKWCode ; 
 scalar_t__* aKWHash ; 
 int* aKWLen ; 
 scalar_t__* aKWNext ; 
 size_t* aKWOffset ; 
 int charMap (char const) ; 
 int /*<<< orphan*/  testcase (int) ; 
 char const toupper (char const) ; 
 char* zKWText ; 

__attribute__((used)) static int keywordCode(const char *z, int n, int *pType){
  int i, j;
  const char *zKW;
  if( n>=2 ){
    i = ((charMap(z[0])*4) ^ (charMap(z[n-1])*3) ^ n) % 127;
    for(i=((int)aKWHash[i])-1; i>=0; i=((int)aKWNext[i])-1){
      if( aKWLen[i]!=n ) continue;
      j = 0;
      zKW = &zKWText[aKWOffset[i]];
#ifdef SQLITE_ASCII
      while( j<n && (z[j]&~0x20)==zKW[j] ){ j++; }
#endif
#ifdef SQLITE_EBCDIC
      while( j<n && toupper(z[j])==zKW[j] ){ j++; }
#endif
      if( j<n ) continue;
      testcase( i==0 ); /* REINDEX */
      testcase( i==1 ); /* INDEXED */
      testcase( i==2 ); /* INDEX */
      testcase( i==3 ); /* DESC */
      testcase( i==4 ); /* ESCAPE */
      testcase( i==5 ); /* EACH */
      testcase( i==6 ); /* CHECK */
      testcase( i==7 ); /* KEY */
      testcase( i==8 ); /* BEFORE */
      testcase( i==9 ); /* FOREIGN */
      testcase( i==10 ); /* FOR */
      testcase( i==11 ); /* IGNORE */
      testcase( i==12 ); /* REGEXP */
      testcase( i==13 ); /* EXPLAIN */
      testcase( i==14 ); /* INSTEAD */
      testcase( i==15 ); /* ADD */
      testcase( i==16 ); /* DATABASE */
      testcase( i==17 ); /* AS */
      testcase( i==18 ); /* SELECT */
      testcase( i==19 ); /* TABLE */
      testcase( i==20 ); /* LEFT */
      testcase( i==21 ); /* THEN */
      testcase( i==22 ); /* END */
      testcase( i==23 ); /* DEFERRABLE */
      testcase( i==24 ); /* ELSE */
      testcase( i==25 ); /* EXCLUDE */
      testcase( i==26 ); /* DELETE */
      testcase( i==27 ); /* TEMPORARY */
      testcase( i==28 ); /* TEMP */
      testcase( i==29 ); /* OR */
      testcase( i==30 ); /* ISNULL */
      testcase( i==31 ); /* NULLS */
      testcase( i==32 ); /* SAVEPOINT */
      testcase( i==33 ); /* INTERSECT */
      testcase( i==34 ); /* TIES */
      testcase( i==35 ); /* NOTNULL */
      testcase( i==36 ); /* NOT */
      testcase( i==37 ); /* NO */
      testcase( i==38 ); /* NULL */
      testcase( i==39 ); /* LIKE */
      testcase( i==40 ); /* EXCEPT */
      testcase( i==41 ); /* TRANSACTION */
      testcase( i==42 ); /* ACTION */
      testcase( i==43 ); /* ON */
      testcase( i==44 ); /* NATURAL */
      testcase( i==45 ); /* ALTER */
      testcase( i==46 ); /* RAISE */
      testcase( i==47 ); /* EXCLUSIVE */
      testcase( i==48 ); /* EXISTS */
      testcase( i==49 ); /* CONSTRAINT */
      testcase( i==50 ); /* INTO */
      testcase( i==51 ); /* OFFSET */
      testcase( i==52 ); /* OF */
      testcase( i==53 ); /* SET */
      testcase( i==54 ); /* TRIGGER */
      testcase( i==55 ); /* REFERENCES */
      testcase( i==56 ); /* UNIQUE */
      testcase( i==57 ); /* QUERY */
      testcase( i==58 ); /* WITHOUT */
      testcase( i==59 ); /* WITH */
      testcase( i==60 ); /* OUTER */
      testcase( i==61 ); /* RELEASE */
      testcase( i==62 ); /* ATTACH */
      testcase( i==63 ); /* HAVING */
      testcase( i==64 ); /* GLOB */
      testcase( i==65 ); /* BEGIN */
      testcase( i==66 ); /* INNER */
      testcase( i==67 ); /* RANGE */
      testcase( i==68 ); /* BETWEEN */
      testcase( i==69 ); /* NOTHING */
      testcase( i==70 ); /* GROUPS */
      testcase( i==71 ); /* GROUP */
      testcase( i==72 ); /* CASCADE */
      testcase( i==73 ); /* ASC */
      testcase( i==74 ); /* DETACH */
      testcase( i==75 ); /* CASE */
      testcase( i==76 ); /* COLLATE */
      testcase( i==77 ); /* CREATE */
      testcase( i==78 ); /* CURRENT_DATE */
      testcase( i==79 ); /* IMMEDIATE */
      testcase( i==80 ); /* JOIN */
      testcase( i==81 ); /* INSERT */
      testcase( i==82 ); /* MATCH */
      testcase( i==83 ); /* PLAN */
      testcase( i==84 ); /* ANALYZE */
      testcase( i==85 ); /* PRAGMA */
      testcase( i==86 ); /* ABORT */
      testcase( i==87 ); /* UPDATE */
      testcase( i==88 ); /* VALUES */
      testcase( i==89 ); /* VIRTUAL */
      testcase( i==90 ); /* LAST */
      testcase( i==91 ); /* WHEN */
      testcase( i==92 ); /* WHERE */
      testcase( i==93 ); /* RECURSIVE */
      testcase( i==94 ); /* AFTER */
      testcase( i==95 ); /* RENAME */
      testcase( i==96 ); /* AND */
      testcase( i==97 ); /* DEFAULT */
      testcase( i==98 ); /* AUTOINCREMENT */
      testcase( i==99 ); /* TO */
      testcase( i==100 ); /* IN */
      testcase( i==101 ); /* CAST */
      testcase( i==102 ); /* COLUMN */
      testcase( i==103 ); /* COMMIT */
      testcase( i==104 ); /* CONFLICT */
      testcase( i==105 ); /* CROSS */
      testcase( i==106 ); /* CURRENT_TIMESTAMP */
      testcase( i==107 ); /* CURRENT_TIME */
      testcase( i==108 ); /* CURRENT */
      testcase( i==109 ); /* PARTITION */
      testcase( i==110 ); /* DEFERRED */
      testcase( i==111 ); /* DISTINCT */
      testcase( i==112 ); /* IS */
      testcase( i==113 ); /* DROP */
      testcase( i==114 ); /* PRECEDING */
      testcase( i==115 ); /* FAIL */
      testcase( i==116 ); /* LIMIT */
      testcase( i==117 ); /* FILTER */
      testcase( i==118 ); /* REPLACE */
      testcase( i==119 ); /* FIRST */
      testcase( i==120 ); /* FOLLOWING */
      testcase( i==121 ); /* FROM */
      testcase( i==122 ); /* FULL */
      testcase( i==123 ); /* IF */
      testcase( i==124 ); /* ORDER */
      testcase( i==125 ); /* RESTRICT */
      testcase( i==126 ); /* OTHERS */
      testcase( i==127 ); /* OVER */
      testcase( i==128 ); /* RIGHT */
      testcase( i==129 ); /* ROLLBACK */
      testcase( i==130 ); /* ROWS */
      testcase( i==131 ); /* ROW */
      testcase( i==132 ); /* UNBOUNDED */
      testcase( i==133 ); /* UNION */
      testcase( i==134 ); /* USING */
      testcase( i==135 ); /* VACUUM */
      testcase( i==136 ); /* VIEW */
      testcase( i==137 ); /* WINDOW */
      testcase( i==138 ); /* DO */
      testcase( i==139 ); /* BY */
      testcase( i==140 ); /* INITIALLY */
      testcase( i==141 ); /* ALL */
      testcase( i==142 ); /* PRIMARY */
      *pType = aKWCode[i];
      break;
    }
  }
  return n;
}