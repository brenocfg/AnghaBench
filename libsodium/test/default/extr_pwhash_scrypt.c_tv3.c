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
 scalar_t__ crypto_pwhash_scryptsalsa208sha256_str_verify (char*,char*,int /*<<< orphan*/ ) ; 
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
        { "^T5H$JYt39n%K*j:W]!1s?vg!:jGi]Ax?..l7[p0v:1jHTpla9;]bUN;?bWyCbtqg "
          "nrDFal+Jxl3,2`#^tFSu%v_+7iYse8-cCkNf!tD=KrW)",
          "$7$B6....1....75gBMAGwfFWZqBdyF3WdTQnWdUsuTiWjG1fF9c1jiSD$tc8RoB3."
          "Em3/zNgMLWo2u00oGIoTyJv4fl3Fl8Tix72" },
        { "bl72h6#y<':MFRZ>B IA1=NRkCKS%W8`1I.2uQxJN0g)N N aTt^4K!Iw5r "
          "H6;crDsv^a55j9tsk'/GqweZn;cdk6+F_St6:#*=?ZCD_lw>.",
          "$7$A6....3....Iahc6qM0.UQJHVgE4h9oa1/"
          "4OWlWLm9CCtfguvz6bQD$QnXCo3M7nIqtry2WKsUZ5gQ.mY0wAlJu."
          "WUhtE8vF66" },
        { "Py "
          ">e.5b+tLo@rL`dC2k@eJ&4eVl!W=JJ4+k&mAt@gt',FS1JjqKW3aq21:]^kna`"
          "mde7kVkN5NrpKUptu)@4*b&?BE_sJMG1=&@`3GBCV]Wg7xwgo7x3El",
          "$7$96..../....f6bEusKt79kK4wdYN0ki2nw4bJQ7P3rN6k3BSigsK/"
          "D$Dsvuw7vXj5xijmrb/NOhdgoyK/OiSIYv88cEtl9Cik7" },
        { "2vj;Um]FKOL27oam(:Uo8+UmSTvb1FD*h?jk_,S=;RDgF-$Fjk?]9yvfxe@fN^!NN("
          "Cuml?+2Raa",
          "$7$86....I....7XwIxLtCx4VphmFeUa6OGuGJrFaIaYzDiLNu/"
          "tyUPhD$U3q5GCEqCWxMwh.YQHDJrlg7FIZgViv9pcXE3h1vg61" },
        { "CT=[9uUoGav,J`kU+348tA50ue#sL:ABZ3QgF+r[#vh:tTOiL>s8tv%,Jeo]jH/"
          "_4^i(*jD-_ku[9Ko[=86 06V",
          "$7$A6....2....R3.bjH6YS9wz9z8Jsj.3weGQ3J80ZZElGw2oVux1TP6$"
          "i5u6lFzXDHaIgYEICinLD6WNaovbiXP8SnLrDRdKgA9" },
        { "J#wNn`hDgOpTHNI.w^1a70%f,.9V_m038H_JIJQln`vdWnn/"
          "rmILR?9H5g(+`;@H(2VosN9Fgk[WEjaBr'yB9Q19-imNa04[Mk5kvGcSn-TV",
          "$7$B6....1....Dj1y.4mF1J9XmT/6IDskYdCLaPFJTq9xcCwXQ1DpT92$92/"
          "hYfZLRq1nTLyIz.uc/dC6wLqwnsoqpkadrCXusm6" },
        { "j4BS38Asa;p)[K+9TY!3YDj<LK-`nLVXQw9%*QfM",
          "$7$B6....1....5Ods8mojVwXJq4AywF/uI9BdMSiJ/zT8hQP/"
          "4cB68VC$nk4ExHNXJ802froj51/1wJTrSZvTIyyK7PecOxRRaz0" },
        { "M.R>Qw+!qJb]>pP :_.9`dxM9k [eR7Y!yL-3)sNs[R,j_/^ "
          "TH=5ny'15>6UXWcQW^6D%XCsO[vN[%ReA-`tV1vW(Nt*0KVK#]45P_A",
          "$7$B6....1....D/"
          "eyk8N5y6Z8YVQEsw521cTx.9zzLuK7YDs1KMMh.o4$alfW8ZbsUWnXc."
          "vqon2zoljVk24Tt1.IsCuo2KurvS2" },
        { "K3S=KyH#)36_?]LxeR8QNKw6X=gFb'ai$C%29V* "
          "tyh^Wo$TN-#Q4qkmtTCf0LLb.^E$0uykkP",
          "$7$B6....1....CuBuU97xgAage8whp/"
          "JNKobo0TFbsORGVbfcQIefyP8$aqalP."
          "XofGViB8EPLONqHma8vs1xc9uTIMYh9CgE.S8" },
        { "Y0!?iQa9M%5ekffW(`",
          "$7$A6....1....TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i4$"
          "a4ik5hGDN7foMuHOW.cp.CtX01UyCeO0.JAG.AHPpx5" },

        /* Invalid pwhash strings */

        { "Y0!?iQa9M%5ekffW(`",
          "$7$A6....1....$TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i4"
          "a4ik5hGDN7foMuHOW.cp.CtX01UyCeO0.JAG.AHPpx5" },
        { "Y0!?iQa9M%5ekffW(`",
          "$7$.6....1....TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i4$"
          "a4ik5hGDN7foMuHOW.cp.CtX01UyCeO0.JAG.AHPpx5" },
        { "Y0!?iQa9M%5ekffW(`",
          "$7$A.....1....TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i4$"
          "a4ik5hGDN7foMuHOW.cp.CtX01UyCeO0.JAG.AHPpx5" },
        { "Y0!?iQa9M%5ekffW(`",
          "$7$A6.........TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i4$"
          "a4ik5hGDN7foMuHOW.cp.CtX01UyCeO0.JAG.AHPpx5" },
        { "Y0!?iQa9M%5ekffW(`",
          "$7$A6....1....TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i44269$"
          "a4ik5hGDN7foMuHOW.cp.CtX01UyCeO0.JAG.AH" },
        { "Y0!?iQa9M%5ekffW(`",
          "$7$A6....1....TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i4$"
          "a4ik5hGDN7foMuHOW.cp.CtX01UyCeO0.JAG.AHPpx54269" },
        { "Y0!?iQa9M%5ekffW(`",
          "$7^A6....1....TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i4$"
          "a4ik5hGDN7foMuHOW.cp.CtX01UyCeO0.JAG.AHPpx5" },
        { "Y0!?iQa9M%5ekffW(`",
          "$7$!6....1....TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i4$"
          "a4ik5hGDN7foMuHOW.cp.CtX01UyCeO0.JAG.AHPpx5" },
        { "Y0!?iQa9M%5ekffW(`",
          "$7$A!....1....TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i4$"
          "a4ik5hGDN7foMuHOW.cp.CtX01UyCeO0.JAG.AHPpx5" },
        { "Y0!?iQa9M%5ekffW(`",
          "$7$A6....!....TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i4$"
          "a4ik5hGDN7foMuHOW.cp.CtX01UyCeO0.JAG.AHPpx5" },
        { "",
          "$7$A6....1....TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i4$"
          "a4ik5hGDN7foMuHOW.cp.CtX01UyCeO0.JAG.AHPpx5" },
        { "Y0!?iQa9M%5ekffW(`",
          "$7fA6....1....TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i4#"
          "a4ik5hGDN7foMuHOW.cp.CtX01UyCeO0.JAG.AHPpx5" },
        { "Y0!?iQa9M%5ekffW(`",
          "$7$AX....1....TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i4$"
          "a4ik5hGDN7foMuHOW.cp.CtX01UyCeO0.JAG.AHPpx5" },
        { "Y0!?iQa9M%5ekffW(`",
          "$7$A6....1!...TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i4$"
          "a4ik5hGDN7foMuHOW.cp.CtX01UyCeO0.JAG.AHPpx5" },
        { "Y0!?iQa9M%5ekffW(`", "$7$A6....1" },
        { "Y0!?iQa9M%5ekffW(`", "$7$" },
        { "Y0!?iQa9M%5ekffW(`", "" },
        { "Y0!?iQa9M%5ekffW(`",
          "$7$A6....1....TrXs5Zk6s8sWHpQgWDIXTR8kUU3s6Jc3s.DtdS8M2i4$" },
        { "test",
          "$7$.6..../.....lgPchkGHqbeONR/xtuXyjCrt9kUSg6NlKFQO0OSxo/$.DbajbPYH9T7sg3fOtcgxvJzzfIgJBIxMkeQ8b24YQ." },
        { "test",
          "$7$z6..../.....lgPchkGHqbeONR/xtuXyjCrt9kUSg6NlKFQO0OSxo/$.DbajbPYH9T7sg3fOtcgxvJzzfIgJBIxMkeQ8b24YQ." },
        { "test",
          "$7$8zzzzzzzzzz.lgPchkGHqbeONR/xtuXyjCrt9kUSg6NlKFQO0OSxo/$.DbajbPYH9T7sg3fOtcgxvJzzfIgJBIxMkeQ8b24YQ." },
        { "test",
          "$7$8.....zzzzz.lgPchkGHqbeONR/xtuXyjCrt9kUSg6NlKFQO0OSxo/$.DbajbPYH9T7sg3fOtcgxvJzzfIgJBIxMkeQ8b24YQ." },
        { "test",
          "$7$86..../..../lgPchkGHqbeONR/xtuXyjCrt9kUSg6NlKFQO0OSxo/$.DbajbPYH9T7sg3fOtcgxvJzzfIgJBIxMkeQ8b24YQ." }
    };
    char * out;
    char * passwd;
    size_t i = 0U;

    do {
        out = (char *) sodium_malloc(strlen(tests[i].out) + 1U);
        assert(out != NULL);
        memcpy(out, tests[i].out, strlen(tests[i].out) + 1U);
        passwd = (char *) sodium_malloc(strlen(tests[i].passwd) + 1U);
        assert(passwd != NULL);
        memcpy(passwd, tests[i].passwd, strlen(tests[i].passwd) + 1U);
        if (crypto_pwhash_scryptsalsa208sha256_str_verify(
                out, passwd, strlen(passwd)) != 0) {
            printf("pwhash_str failure: [%u]\n", (unsigned int) i);
        }
        sodium_free(out);
        sodium_free(passwd);
    } while (++i < (sizeof tests) / (sizeof tests[0]));
}