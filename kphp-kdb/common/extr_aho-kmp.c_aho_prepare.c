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
 int AHO_MAX_L ; 
 int AHO_MAX_N ; 
 int AHO_MAX_S ; 
 int* C ; 
 int* KA ; 
 int* KB ; 
 int KL ; 
 int KN ; 
 int* KS ; 
 int* L ; 
 int** S ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  sort_str (int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 

int aho_prepare (int cnt, char *s[]) {
  int i, j;

  if (cnt <= 0 || cnt > AHO_MAX_N) {
    return -1;
  }

  int SL = 0; 
  
  for (i = 0; i < cnt; i++) {
    L[i] = strlen (s[i]);
    if (L[i] <= 0 || L[i] > AHO_MAX_L) {
      return -1;
    }
    SL += L[i] + 1;
  }

  if (SL >= AHO_MAX_S) {
    return -1;
  }

  for (i = 0; i < cnt; i++) {
    int N = L[i], q = 0;
    char *P = s[i];
    int A[N + 1];

    A[0] = -1;
    A[1] = 0;
    j = 1;
    while (j < N) {
      while (q >= 0 && P[j] != P[q]) {
        q = A[q];
      }
      A[++j] = ++q;
    }

    for (j = 0; j < cnt; j++) {
      if (i == j || L[j] < N) {
        continue;
      }

      q = 0;
      char *T = s[j];
      while (*T) {
        while (q >= 0 && *T != P[q]) {
          q = A[q];
        }
        if (++q == N) {
          break;
        }
        T++;
      }

      if (q == N) {
        break;
      }
    }

    if (q == N) {
      L[i] = 0;
    }
  }

  int p = 0;
  for (i = 0; i < cnt; i++) {
    if (L[i] > 0) {
      L[p] = L[i];
      S[p++] = s[i];
    }
  }

  KN = p;

  sort_str (0, KN - 1);

  int MaxL = 0;
  KL = 1;

  for (i = 0; i < KN; i++) {
    memcpy (KS + KL, S[i], L[i] + 1);
    S[i] = KS + KL;
    C[i] = 0;
    KL += L[i] + 1;
    if (L[i] > MaxL) {
      MaxL = L[i];
    }
  }
  assert (KL <= AHO_MAX_S);

  KA[0] = -1;

  int l;
  for (l = 0; l <= MaxL; l++) {
    int pc = -1, ps = -256, cc = -1, v = -1;
    
    for (i = 0; i < KN; i++) {
      if (L[i] < l) {
        continue;
      }
      int u = S[i] + l - KS;
      if (L[i] == l) {
        KB[u] = (1 << i);
      } else {
        KB[u] = 0;
      }
      if (pc != C[i]) {
        int q = KA[u-1];
        while (q > 0 && S[i][l-1] != KS[q]) {
          q = KA[q];
        }
        KA[u] = q + 1;
        pc = C[i];
        ps = S[i][l];
        cc = i;
        v = u;
      } else if (ps != S[i][l]) {
        KA[u] = KA[v];
        KA[v] = u;
        ps = S[i][l];
        cc = i;
        v = u;
      }
      C[i] = cc;
    }
  } 
  return KL;
}